
#include "mydcmotor.h"

MyDCMotor* pmt1;

int angle;
int now = 0;
int plus = +1;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pmt1 = new MyDCMotor(1);
  pmt1->setSpeed(255);
  pmt1->run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  pmt1->run(BACKWARD);
  delay(3000);
  pmt1->run(RELEASE);
  delay(3000);
}
