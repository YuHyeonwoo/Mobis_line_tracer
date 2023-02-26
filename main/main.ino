
#include "obstacle.h"
#include "customarduino.h"
#include "tracemodel.h"
#include "checkClap.h"

Obstacle obstacle;
Clap clap;
TraceModel* traceModel;

void setup() {
  // put your setup code here, to run once:
  obstacle.pinSet(10, 9);
  clap.setPin(A2);
  // M1 : ENA(9), IN1(8), IN2(7)
  // M2 : ENB(10), IN3(6), IN4(5)
  // M3 : ENA(10), IN1(12), IN2(13)
  // M4 : ENB(11), IN3(8), IN4(9)
  // TraceModel(int motor1_en, int motor1_in1, int motor1_in2, int motor2_en, int motor2_in1, int motor2_in2, int sp_f, int sp_c);
  tracemodel -> new TraceModel(9,8,7,10,6,5,160,130);
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
