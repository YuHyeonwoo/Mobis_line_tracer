]
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "obstacle.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  useBuzzerPin();
  useIRSensor();
}

void loop() {
  // put your main code here, to run repeatedly
  clap();
  if(oneClap()){
    moveFaster();
  }else if(twoClap()){
    moveSlower();
  }

  if(checkOpstacle()){
    stopSound();
    MoveStop();
    return;
  }
  Move();
}