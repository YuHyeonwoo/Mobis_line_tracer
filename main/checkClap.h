#ifndef __CHECKCLAP_H__
#define __CHECKCLAH_H__

#include "customarduino.h"

enum state {nothing, clap1, clap1_waiting, clap1_end, clap2, clap2_end};
/*
nothing : 평범한 상황 0초
clap1 : 박수 한번 친 이후, 다음 소리를 듣지 않는 상태 0초~0.15초
clap1_waiting : 박수 한번 친 이후, 다음 소리를 기다리는 상태 0.15초 ~ 0.6초
clap1_end : 박수 한번 친 이후 0.6초가 지나면
clap2 : 박수 두번 친 이후, 0.75초까지
clap2_end : 박수 두번끝
*/


class Clap{
    int LM_Pin;
    int now_state;
    long first_clap_time;
    int isLoud(int sound);
public:
    void setPin(int LM_Pin);
    void checkClap(); // 현재 박수소리가 들리는 것에 따라 now_state 변화
    int getClap(); // 박수상태 반환 /  박수 안치면 0, 한번 쳤으면 1, 두번 쳤으면 2, 반환후 now_state 초기화
};

void Clap::setPin(int LM_Pin){
    this->LM_Pin = LM_Pin;
    pinMode_custom(LM_Pin, INPUT);
}


int Clap::isLoud(int sound){
  if(sound < 400) return 1;
  //if(sound == 1)return 1;
  return 0;
}

void Clap::checkClap(){
    int sound = analogRead_custom(LM_Pin);
    //int sound = digitalRead_custom(LM_Pin);
    if(isLoud(sound) && now_state == nothing){ // nothing에서 박수 소리를 들으면
        first_clap_time = millis();    
        now_state = clap1;
    }
    else if(now_state == clap1 && (millis()-first_clap_time) >= 150){ // clap1에서 0.15초가 지나면
        now_state = clap1_waiting;
    }
    else if(now_state == clap1_waiting && (millis()-first_clap_time) >= 600){ // clap_waiting인 상태에서 0.6초가 되면
        now_state = clap1_end;
    }
    else if(now_state == clap1_waiting && isLoud(sound)){ // clap_waiting인 상태에서 박수소리를 들으면    
        now_state = clap2;
    }
    else if(now_state == clap2 && (millis()-first_clap_time) >= 750){ // clap2인 상태에서 시간이 지나면    
        now_state = clap2_end;
    }
}



int Clap::getClap(){
    this->checkClap();
    if(now_state == clap1_end){
        now_state = nothing;
        return 1;
    }else if(now_state == clap2_end){
        now_state = nothing;
        return 2;
    }else{
        return 0;
    }
}

#endif