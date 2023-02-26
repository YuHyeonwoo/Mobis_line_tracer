
#include "mydcmotor.h"

MyDCMotor* pmt1;

int angle;
int now = 0;
int plus = +1;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pmt1 = new MyDCMotor(10,11,9);
  pmt1->stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  pmt1->run();
  delay(3000);
  pmt1->run_backward();
  delay(3000);
}
