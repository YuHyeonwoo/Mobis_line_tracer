#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Arduino.h"

int Tones[7] = {261, 294, 330, 349, 392, 440, 494};                   // 도, 레, 미, 파, 솔, 라, 시

class Obstacle{
  int Buzzer_Pin;
  int IR_Sensor_Pin;
public:
  void pinSet(int Buzzer_Pin, int IR_Sensor_Pin); // 부저번호, 핀번호
  int checkObstacle(); // 장애물이 인식되면 1, 아니면 0 출력
  void stopSound(); // 경고음을 울림
};

void Obstacle::pinSet(int Buzzer_Pin, int IR_Sensor_Pin){
  this->Buzzer_Pin = Buzzer_Pin;
  this->IR_Sensor_Pin = IR_Sensor_Pin;
  pinMode(this->Buzzer_Pin, OUTPUT);
  pinMode(this->IR_Sensor_Pin, INPUT);
}

int Obstacle::checkObstacle(){
  return !digitalRead(this->IR_Sensor_Pin);
}

void Obstacle::stopSound(){
    tone(Buzzer_Pin, Tones[5]);
    delay(300);
    noTone(Buzzer_Pin);
    delay(300);
}

// void arriveSound(){
//     for(int i = 0; i<3; i++){
//       tone(Buzzer_Pin, Tones[0]);
//       delay(300);
//       tone(Buzzer_Pin, Tones[2]);
//       delay(300);
//       tone(Buzzer_Pin, Tones[4]);
//       delay(300);
//     }
//     tone(Buzzer_Pin, Tones[6]);
//     delay(300);
//     noTone(Buzzer_Pin);
// }



#endif