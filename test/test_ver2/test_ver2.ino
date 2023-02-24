#include <SoftwareSerial.h>
#include <AFMotor.h>

// Motor pins

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
int LINE_L = A0;
int LINE_R = A5;
int speed_L = 0; // 모터 pwm value
int speed_R = 0; // 모터 pwm value

// Drives two motors according to the given pwm values.
void drive(int pwmA, int pwmB);

void setup() {
  Serial.begin(115200);

  // motor_Dirver
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);

  // lineTracer
  pinMode(LINE_R, INPUT);   
  pinMode(LINE_L, INPUT);  
}

void loop() {

  // drive line following robot
  // if (speed > 0) {
    // 왼쪽 라인트레이서가 바깥으로 나가면 왼쪽 휠을 더 빠르게
    // 오른쪽 라인트레이서가 바깥으로 나가면 오른쪽 휠을 더 빠르게
    int val_L = analogRead(LINE_L);
    int val_R = analogRead(LINE_R);
    speed_L = map(val_L,0,810,-180,180);
    speed_R = map(val_R,0,810,-180,180);
    Serial.print("Left : ");
    Serial.print(val_L);
    Serial.print("   Right : ");
    Serial.print(val_R);    
    Serial.print("   speed_L : ");
    Serial.print(speed_L); 
    Serial.print("   speed_R : ");
    Serial.println(speed_R); 
    if (val_L > 410) { // 왼쪽이 검은 선안에 있을 경우 -> 오른휠 조정
      if(val_R > 410){
        drive(speed_L, speed_R);
      }
      else{
        drive(speed_L, 0);
      }
    } 
    else { // 왼쪽이 검은 선 안을 벗어날 경우
      if(val_R > 410){
        drive(0, speed_R);        
      }
      else{
        drive(-abs(speed_L), -abs(speed_R)); // 둘다 흰색으로 벗어남
      }
    }

}

void drive(int pwmA, int pwmB) {
  // MOTOR 1 direction
  if (pwmA > 0) { // 오른휠 조정
    motor1.run(FORWARD);
  } else if (pwmA < 0) {
    motor1.run(BACKWARD);
  } else {
    motor1.run(RELEASE);
  }

  // // MOTOR 2 direction
  if (pwmB > 0) {
    motor2.run(FORWARD);
  } else if (pwmB < 0) {
    motor2.run(BACKWARD);
  } else {
    motor2.run(RELEASE);
  }

  // speed of motors
  motor1.setSpeed(abs(pwmA));
  motor2.setSpeed(abs(pwmB));
}
