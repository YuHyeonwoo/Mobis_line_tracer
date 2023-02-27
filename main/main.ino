#include "obstacle.h"
#include "customarduino.h"
#include "tracemodel_library.h"
#include "checkClap.h"

#define sp_f 220
#define sp_c 220
#define motor1_pin 1
#define motor2_pin 2


Obstacle obstacle;
Clap clap;

TraceModel* traceModel;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  obstacle.pinSet(10, 9);
  clap.setPin(A2);
  // M1 : ENA(9), IN1(8), IN2(7)
  // M2 : ENB(10), IN3(6), IN4(5)
  // M3 : ENA(10), IN1(12), IN2(13)
  // M4 : ENB(11), IN3(8), IN4(9)

  // ENA(11), IN1(12), IN2(13)
  // ENB(3), IN1(12), IN2(13)
  // TraceModel(int motor1_en, int motor1_in1, int motor1_in2, int motor2_en, int motor2_in1, int motor2_in2, int sp_f, int sp_c);
  // TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin);
  traceModel = new TraceModel(sp_f,sp_c,motor1_pin,motor2_pin);
}
void loop() {

  if(obstacle.checkObstacle()){
    obstacle.stopSound();
    return;
  }
  int clapNum = clap.getClap();
  switch(clapNum){
    case 1:
      traceModel->Slow();
      break;
    case 2:
      traceModel->Fast();
      break;
    default:
     break;
  }
  traceModel->Go();
}