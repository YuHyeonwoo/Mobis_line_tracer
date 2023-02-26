#include "obstacle.h"
#include "customarduino.h"
#include "tracemodel.h"
#include "checkClap.h"

Obstacle obstacle;
Clap clap;
//TraceModel traceModel;

void setup() {
  // // put your setup code here, to run once:
  Serial.begin(9600);
  obstacle.pinSet(10, 9);
  clap.setPin(A2);
  // traceModel.TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin);
}

void loop() {

  if(obstacle.checkObstacle()){
    obstacle.stopSound();
    return;
  }
  int clapNum = clap.getClap();
  switch(clapNum){
    case 1:
      Serial.println("clap 1");
      //traceModel.slow();
      break;
    case 2:
      Serial.println("clap 2");
      //traceModel.fast();
      break;
    default:
     break;
  }
  // traceModel.go();
}