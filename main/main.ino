// #include "./header/obstacle.h"
// #include "./header/customarduino.h"
// #include "./header/tracemodel_library.h"
// #include "./header/checkClap.h"

// #define sp_f 170
// #define sp_c 170
// #define motor1_pin 4
// #define motor2_pin 3


// Obstacle obstacle;
// Clap clap;

// TraceModel* traceModel;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   obstacle.pinSet(10, 9);
//   clap.setPin(A2);
//   traceModel = new TraceModel(sp_f,sp_c,motor1_pin,motor2_pin);
// }
// void loop() {
//   traceModel->Go();
// }

#include "./header/obstacle.h"
#include "./header/customarduino.h"
#include "./header/tracemodel_library.h"
#include "./header/checkClap.h"

#define sp_f 140
#define sp_c 140
#define motor1_pin 4
#define motor2_pin 3


Obstacle obstacle;
Clap clap;

TraceModel* traceModel;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  obstacle.pinSet(10, 9);
  clap.setPin(A3);
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

  switch(clapNum){
    case 1:
      if (traceModel->Slow())
        tone_custom(10, 400, 300);
      break;
    case 2:
      if (traceModel->Fast())
        tone_custom(10, 600, 300);
      break;
  }

  traceModel->Go();
}