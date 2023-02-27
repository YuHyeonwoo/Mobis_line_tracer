#include "./header/obstacle.h"
#include "./header/customarduino.h"
#include "./header/tracemodel_library.h"
#include "./header/checkClap.h"

#define sp_f 210
#define sp_c 210
#define motor1_pin 4
#define motor2_pin 3


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
    traceModel->Stop();
    obstacle.stopSound();
    delay(600);
    return;
  }
  int clapNum = clap.getClap();

  traceModel->Go();
  delay(20);
}