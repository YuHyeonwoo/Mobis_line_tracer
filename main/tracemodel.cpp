#include "tracemodel.h"

TraceModel :: TraceModel(int motor1_en, int motor1_in1, int motor1_in2, int motor2_en, int motor2_in1, int motor2_in2, int sp_f, int sp_c){
  pm1 = new MyDCMotor(motor1_in1, motor1_in2, motor1_en);
  pm2 = new MyDCMotor(motor2_in1, motor2_in2, motor2_en);
  speed_fro = sp_f; speed_cur = sp_c;
  stat[0] = 0; stat[1] = 0;
  speedArr[0] = 0; speedArr[1] = 0;
  // motor_Dirver
  pm1->setSpeed(speed_fro);
  pm1->run(RELEASE);
  pm2->setSpeed(speed_fro);
  pm2->run(RELEASE);

  // lineTracer
  pinMode_custom(line_r, INPUT);
  pinMode_custom(line_l, INPUT); 
}

void TraceModel :: Go(){
  // put your main code here, to run repeatedly:
  int val_L = digitalRead_custom(line_l);  // 센서 값을 읽어와서
  int val_R = digitalRead_custom(line_r);  // 센서 값을 읽어와서

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
    delay(500);
    Move('s');
    //delay(700);
  }
}

int TraceModel :: isChange(int type, int speed){
  if(speedArr[type] != speed) { // 스피드가 바뀌어야 하는 경우
    return 1;
  }
  return 0;
}

void TraceModel :: Move(char cmd){
  switch(cmd){
    case 'f': // front
      pm1->run(FORWARD);
      pm2->run(FORWARD);
      Serial.println("front");
      break;
    
    case 'b': // back
      pm1->run(BACKWARD);
      pm2->run(BACKWARD);
      Serial.println("back");
      break;

    case 'r': // right
      pm1->run(FORWARD);
      pm2->run(BACKWARD);
      Serial.println("right");
      break;
    
    case 'l': // left
      pm1->run(BACKWARD);
      pm2->run(FORWARD);  
      Serial.println("left");
      break;
    
    default:
      pm1->run(RELEASE);
      pm2->run(RELEASE);
      Serial.println("stop");
      break;
  }
}

void TraceModel :: Speed(int type, int speed){
  if(type == 0){
    pm1->run(RELEASE);
    pm1->setSpeed(speed);
    speedArr[0] = speed;
  }
  else if(type == 1){
    pm2->run(RELEASE);
    pm2->setSpeed(speed);
    speedArr[1] = speed;
  }
  //delay(100);
}
