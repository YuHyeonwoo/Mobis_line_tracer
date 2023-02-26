
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "obstacle.h"

Obstacle obstacle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  obstacle.pinSet(10, 9);
}

void loop() {
  // put your main code here, to run repeatedly
  clap();
  if(oneClap()){
    moveFaster();
  }else if(twoClap()){
    moveSlower();
  }

  if(obstacle.checkObstacle()){
    obstacle.stopSound();
    MoveStop();
    return;
  }
  Move();
}