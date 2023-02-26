#include "obstacle.h"

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