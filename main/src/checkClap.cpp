#include "../header/checkClap.h"

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
