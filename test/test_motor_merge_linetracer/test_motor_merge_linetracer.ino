#include <SoftwareSerial.h>
#include <AFMotor.h>
//#define end;

// motor driver
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// line_tracer
int line_r = A0;
int line_l = A5;

void setup() {
  Serial.begin(9600);

  // motor_Dirver
  motor1.setSpeed(150);
  motor1.run(RELEASE);
  motor2.setSpeed(150);
  motor2.run(RELEASE);

  // lineTracer
  pinMode(line_r, INPUT);   // 라인트레이서 센서는 '입력'
  pinMode(line_l, INPUT);   // 라인트레이서 센서는 '입력'
}

void Speed(int type, int speed){
  if(type == 1){
    motor1.run(RELEASE);
    motor1.setSpeed(speed);
  }
  else if(type == 2){
    motor2.run(RELEASE);
    motor2.setSpeed(speed);
  }
  //delay(100);
}

void loop() {
#ifndef end
  // put your main code here, to run repeatedly:
  int val_L = digitalRead(line_l);  // 센서 값을 읽어와서
  int val_R = digitalRead(line_r);  // 센서 값을 읽어와서
  Serial.print("Left : ");
  Serial.println(val_L);
  Serial.print("Right : ");
  Serial.println(val_R);
  
  if (val_R == LOW && val_L == LOW){ // 둘다 검은색X
    Speed(1,150);
    Speed(2,150);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    //delay(500);
  }
  
  else if (val_R == LOW){     // 왼쪽이 검은색
    Speed(1,130);
    motor1.run(BACKWARD);
    motor2.run(FORWARD);          
   //delay(500);
  }
  else if (val_L == LOW){ // 오른쪽이 검은색
    motor1.run(FORWARD);
    Speed(2,130);
    motor2.run(BACKWARD);
    //delay(500);
  } 
  else{               // 둘다 검은색
    Speed(1,150);
    Speed(2,150);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(1000);
  }
#endif
  
  
}