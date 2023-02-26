#include "Arduino.h"
#include "mydcmotor.h"

MyDCMotor::MyDCMotor(uint8_t pwm_pin){
    pinMode(pwm_pin,OUTPUT);
}

MyDCMotor::MyDCMotor(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin) {
    // 모터 제어 핀을 출력으로 설정
    pinMode(in1_pin, OUTPUT);
    pinMode(in2_pin, OUTPUT);
    pinMode(pwm_pin, OUTPUT);

    // 멤버 변수 초기화
    in1_pin_ = in1_pin;
    in2_pin_ = in2_pin;
    pwm_pin_ = pwm_pin;
}

void MyDCMotor::run() {
    // 모터 방향을 전진으로 설정
    digitalWrite(in1_pin_, HIGH);
    digitalWrite(in2_pin_, LOW);

    // PWM 신호를 출력하여 모터 속도 조절
    analogWrite(pwm_pin_, now_speed_);
}

void MyDCMotor::run_backward() {
    // 모터 방향을 후진으로 설정
    digitalWrite(in1_pin_, LOW);
    digitalWrite(in2_pin_, HIGH);

    // PWM 신호를 출력하여 모터 속도 조절
    analogWrite(pwm_pin_, now_speed_);
}

void MyDCMotor::stop() {
    analogWrite(pwm_pin_, 0);
}

void MyDCMotor::setSpeed(uint8_t speed){
    now_speed_ = speed;
}

void MyDCMotor::servo(uint8_t i){
    digitalWrite(9, HIGH);  
    delay(i);     
    digitalWrite(9, LOW); 
    delay(180-i);    
    // analogWrite(pwm_pin_, now_speed_);
}