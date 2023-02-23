#include <SoftwareSerial.h>
#include <AFMotor.h>
#define end;

// motor driver
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// line_tracer
int line_r = A0;
int line_l = A5;

void setup() {
  Serial.begin(9600);

  // motor_Dirver
  motor1.setSpeed(250);
  motor1.run(RELEASE);
  motor2.setSpeed(250);
  motor2.run(RELEASE);

  // lineTracer
  pinMode(line_r, INPUT);   // 라인트레이서 센서는 '입력'
  pinMode(line_l, INPUT);   // 라인트레이서 센서는 '입력'
}

void loop() {
#ifndef end
  // put your main code here, to run repeatedly:
  int val_L = digitalRead(line_l);  // 센서 값을 읽어와서
  int val_R = digitalRead(line_r);  // 센서 값을 읽어와서
  Serial.println(val_L);
  Serial.println(val_R);

  if (val_R == LOW && val_L == LOW){ // 둘다 검은색으로 들어올 때
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    //delay(500);
  }
  
  if (val_R == LOW){     // 우회전
    motor1.run(RELEASE);
    motor2.run(FORWARD);          
   //delay(500);
  }
  else if (val_L == LOW){ // 좌회전
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    //delay(500);
  } 
  else{               // 검정색 주행선을 벗어나면
    motor1.run(FORWARD);
    motor2.run(FORWARD);        // Buzzer에서 소리가 난다
    //delay(500);
  }
#endif
  
  
}
