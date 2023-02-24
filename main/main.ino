#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "obstacle.h"
#include "tracemodel.h"

TraceModel* ptrm;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  useBuzzerPin();
  useIRSensor();
  ptrm = new TraceModel(210,210,1,2);
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

  ptrm->Go();
}