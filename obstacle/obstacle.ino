#include <SoftwareSerial.h>
#include <AFMotor.h>

int Buzzer_Pin = 10;
int Tones[7] = {261, 294, 330, 349, 392, 440, 494};                   // 도, 레, 미, 파, 솔, 라, 시
    
void stopSound();
void arriveSound();

void stopSound(){
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

void arriveSound(){
    for(int i = 0; i<3; i++){
      tone(Buzzer_Pin, Tones[5]);
      delay(300);
      noTone(Buzzer_Pin);
      delay(300);
    }    
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Buzzer_Pin, OUTPUT);
  stopSound();
  delay(1000);
  arriveSound();
}

void loop() {
  // put your main code here, to run repeatedly:

}
