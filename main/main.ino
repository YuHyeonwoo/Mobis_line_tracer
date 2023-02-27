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
  traceModel = new TraceModel(sp_f,sp_c,motor1_pin,motor2_pin);
}
void loop() {

  if(obstacle.checkObstacle()){
    obstacle.stopSound();
    traceModel->Stop();
    delay(600);
    return;
  }
  int clapNum = clap.getClap();

  traceModel->Go();
  //delay(20);
}