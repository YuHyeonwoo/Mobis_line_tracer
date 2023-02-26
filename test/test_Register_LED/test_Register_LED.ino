#include "customarduino.h"

void setup() {
  // put your setup code here, to run once:
  // DDRD |= (1 << 7); // 7번 포트를 OUTPUT으로
  pinMode_custom(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // PORTD |= (1 << 7); // 7번 포트에 전압 인가
  for(int i=0; i<=250; i++){
    analogWrite_custom(3,i);
    delay(20);
  }
  for(int i=250; i>=0; i--){
    analogWrite_custom(3,i);
    delay(20);
  }
  // PORTD &= ~(1 << 7); // 7번 포트 전압 해제
  // delay(3000);
}
