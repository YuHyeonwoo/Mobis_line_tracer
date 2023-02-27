#include "../header/tracemodel_library.h"

TraceModel :: TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin){
  pm1 = new AF_DCMotor(motor1_pin);
  pm2 = new AF_DCMotor(motor2_pin);
  speed_fro = sp_f; speed_cur = sp_c;
  stat[0] = 0; stat[1] = 0;
  speedArr[0] = 0; speedArr[1] = 0;
  // motor_Dirver
  pm1->setSpeed(speed_fro);
  pm1->run(RELEASE);
  pm2->setSpeed(speed_fro);
  pm2->run(RELEASE);

  // lineTracer
  pinMode(line_r, INPUT);
  pinMode(line_l, INPUT); 
}

void TraceModel :: Go(){
  // put your main code here, to run repeatedly:
  int val_L = digitalRead(line_l);  // 센서 값을 읽어와서
  int val_R = digitalRead(line_r);  // 센서 값을 읽어와서

  if (val_R == LOW && val_L == LOW){ // 둘다 검은색X
    if(isChange(0,speed_fro)){
      Speed(0,speed_fro);
    }
    if(isChange(1,speed_fro)){
      Speed(1,speed_fro);
    }
    Move('f');
  }
  
  else if (val_R == LOW){     // 왼쪽이 검은색
    if(isChange(0,speed_cur)){
      Speed(0,speed_cur);
    }
    if(isChange(1,speed_fro)){
      Speed(1,speed_fro);
    }
    Move('l');   
  }
  else if (val_L == LOW){ // 오른쪽이 검은색
    if(isChange(0,speed_fro)){
      Speed(0,speed_fro);
    }
    if(isChange(1,speed_cur)){
      Speed(1,speed_cur);
    }
    Move('r');
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
      break;
    
    case 'b': // back
      pm1->run(BACKWARD);
      pm2->run(BACKWARD);
      break;

    case 'r': // right
      pm1->run(FORWARD);
      pm2->run(BACKWARD);
      break;
    
    case 'l': // left
      pm1->run(BACKWARD);
      pm2->run(FORWARD);  
      break;
    
    default:
      pm1->run(RELEASE);
      pm2->run(RELEASE);
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

void TraceModel :: Stop(){
  Move('s');
}

void TraceModel :: Slow(){
  if(speed_fro > 100 && speed_cur > 100){
    speed_fro -= 50;
    speed_cur -= 50;
  }
}

void TraceModel :: Fast(){
  if(speed_fro < 205 && speed_cur < 205){
    speed_fro += 50;
    speed_cur += 50;
  }
}
