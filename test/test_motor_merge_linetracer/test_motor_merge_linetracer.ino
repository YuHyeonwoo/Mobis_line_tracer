#include <SoftwareSerial.h>
#include <AFMotor.h>

// motor driver
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// line_tracer
int line_r = 7;
int line_l = 8;

void setup() {
  // motor_Dirver
  Serial.begin(9600);
  motor1.setSpeed(250);
  motor1.run(RELEASE);
  motor2.setSpeed(250);
  motor2.run(RELEASE);

  // lineTracer
  pinMode(line_r, INPUT);   // 라인트레이서 센서는 '입력'
  pinMode(line_l, INPUT);   // 라인트레이서 센서는 '입력'
}

void loop() {
  // put your main code here, to run repeatedly:

}
