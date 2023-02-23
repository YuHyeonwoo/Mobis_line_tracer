#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(250);
  motor1.run(RELEASE);
  motor2.setSpeed(250);
  motor2.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.run(RELEASE);
  motor2.run(RELEASE);

}
