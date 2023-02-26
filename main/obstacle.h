#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "customarduino.h"

int Tones[7] = {261, 294, 330, 349, 392, 440, 494};                   // 도, 레, 미, 파, 솔, 라, 시

class Obstacle{
  int Buzzer_Pin;
  int IR_Sensor_Pin;
public:
  void pinSet_custom(int Buzzer_Pin, int IR_Sensor_Pin); // 부저번호, 핀번호
  int checkObstacle(); // 장애물이 인식되면 1, 아니면 0 출력
  void stopSound(); // 경고음을 울림
};

void Obstacle::pinSet(int Buzzer_Pin, int IR_Sensor_Pin){
  this->Buzzer_Pin = Buzzer_Pin;
  this->IR_Sensor_Pin = IR_Sensor_Pin;
  pinMode_custom(this->Buzzer_Pin, OUTPUT);
  pinMode_custom(this->IR_Sensor_Pin, INPUT);
}

int Obstacle::checkObstacle(){
  return !digitalRead_custom(this->IR_Sensor_Pin);
}

void Obstacle::stopSound(){
    tone(Buzzer_Pin, Tones[5]);
    delay(300);
    noTone(Buzzer_Pin);
    delay(300);
}


#endif