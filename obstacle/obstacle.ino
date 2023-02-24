#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "obstacle.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // stopSound();
  // delay(1000);
  // arriveSound();
}

void loop() {
  // put your main code here, to run repeatedly
  if (checkOpstacle == 1){
    stopSound();
  }
}
