
#include "obstacle.h"
#include "customarduino.h"
#include "tracemodel.h"
#include "checkClap.h"

Obstacle obstacle;
Clap clap;
TraceModel traceModel;

void setup() {
  // put your setup code here, to run once:
  obstacle.pinSet(10, 9);
  clap.setPin(A2);
  traceModel.TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin);
}

void loop() {
  if(obstacle.checkObstacle()){
    obstacle.stopSound();
    return;
  }
  int clapNum = clap.getClap();
  switch(clapNum){
    case 1:
      //traceModel.slow();
      break;
    case 2:
      //traceModel.fast();
      break;
    default:
     break;
  }
  traceModel.go();
}
