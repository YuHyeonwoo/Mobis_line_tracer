#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

int Buzzer_Pin = 10;
int IR_Sensor_Pin = 9;
int Tones[7] = {261, 294, 330, 349, 392, 440, 494};                   // 도, 레, 미, 파, 솔, 라, 시


void startSound();
void stopSound();
void arriveSound();
int checkOpstacle();
void startObstacleCheck();

void useBuzzerPin(){
    pinMode(Buzzer_Pin, OUTPUT);
}

void useIRSensor(){
    pinMode(IR_Sensor_Pin, INPUT);
}

void startObstacleCheck(){
  if (checkOpstacle() == 1){
    stopSound();
  }
}

int checkOpstacle(){
  return !digitalRead(IR_Sensor_Pin);
}

void arriveSound(){
    for(int i = 0; i<3; i++){
      tone(Buzzer_Pin, Tones[0]);
      delay(300);
      tone(Buzzer_Pin, Tones[2]);
      delay(300);
      tone(Buzzer_Pin, Tones[4]);
      delay(300);
    }
    tone(Buzzer_Pin, Tones[6]);
    delay(300);
    noTone(Buzzer_Pin);
}

void stopSound(){
    tone(Buzzer_Pin, Tones[5]);
    delay(300);
    noTone(Buzzer_Pin);
    delay(300);
}

#endif