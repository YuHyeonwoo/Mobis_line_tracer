#include <SoftwareSerial.h>
#include <AFMotor.h>
#define speed_fro 150
#define speed_cur 140
//#define end;

// motor driver
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// line_tracer
int line_r = A0;
int line_l = A5;

int stat[2] = {0,0}; // idx : { 좌, 우 }, 0 : 정지 -1 : BACKWARD, 1 : FORWARD
int speedArr[2] = {speed_fro,speed_cur};

void setup() {
  Serial.begin(9600);

  // motor_Dirver
  motor1.setSpeed(speed_fro);
  motor1.run(RELEASE);
  motor2.setSpeed(speed_fro);
  motor2.run(RELEASE);

  // lineTracer
  pinMode(line_r, INPUT);   // 라인트레이서 센서는 '입력'
  pinMode(line_l, INPUT);   // 라인트레이서 센서는 '입력'
}

void Speed(int type, int speed){
  if(type == 0){
    motor1.run(RELEASE);
    motor1.setSpeed(speed);
  }
  else if(type == 1){
    motor2.run(RELEASE);
    motor2.setSpeed(speed);
  }
  //delay(100);
}

void Move(char cmd){
  switch(cmd){
    case 'f': // front
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      break;
    
    case 'b': // back
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      break;

    case 'r': // right
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      break;
    
    case 'l': // left
      motor1.run(BACKWARD);
      motor2.run(FORWARD);  
      break;
    
    default:
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      break;
  }
}

int isChange(int type, int speed){
  if(speedArr[type] != speed) { // 스피드가 바뀌어야 하는 경우
    return 1;
  }
  return 0;
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
    if(isChange(0,speed_fro)){
      Speed(0,speed_fro);
    }
    if(isChange(1,speed_fro)){
      Speed(1,speed_fro);
    }
    Move('f');
    //delay(500);
  }
  
  else if (val_R == LOW){     // 왼쪽이 검은색
    if(isChange(0,speed_cur)){
      Speed(0,speed_cur);
    }
    if(isChange(1,speed_fro)){
      Speed(1,speed_fro);
    }
    Move('l');        
   //delay(500);
  }
  else if (val_L == LOW){ // 오른쪽이 검은색
    if(isChange(0,speed_fro)){
      Speed(0,speed_fro);
    }
    if(isChange(1,speed_cur)){
      Speed(1,speed_cur);
    }
    Move('r');
    //delay(500);
  } 
  else{               // 둘다 검은색
    if(isChange(0,speed_fro)){
      Speed(0,speed_fro);
    }
    if(isChange(1,speed_fro)){
      Speed(1,speed_fro);
    }
    Move('b');
    delay(700);
  }
#endif
  
  
}