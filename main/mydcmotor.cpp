#include "customarduino.h"
#include "mydcmotor.h"

MyDCMotor::MyDCMotor(uint8_t in1_pin, uint8_t in2_pin, uint8_t en_pin) {
    // 모터 제어 핀을 출력으로 설정
    pinMode_custom(in1_pin, INPUT);
    pinMode_custom(in2_pin, INPUT);
    pinMode_custom(en_pin, OUTPUT);

    // 멤버 변수 초기화
    in1_pin_ = in1_pin;
    in2_pin_ = in2_pin;
    en_pin_ = en_pin;
}

void MyDCMotor::run_forward() {
    // 모터 방향을 전진으로 설정
    digitalWrite_custom(in1_pin_, HIGH);
    digitalWrite_custom(in2_pin_, LOW);

    // PWM 신호를 출력하여 모터 속도 조절
    analogWrite_custom(en_pin_, now_speed_);
}

void MyDCMotor::run_backward() {
    // 모터 방향을 후진으로 설정
    digitalWrite_custom(in1_pin_, LOW);
    digitalWrite_custom(in2_pin_, HIGH);

    // PWM 신호를 출력하여 모터 속도 조절
    analogWrite_custom(en_pin_, now_speed_);
}

void MyDCMotor::stop() {
    digitalWrite_custom(in1_pin_, LOW);
    digitalWrite_custom(in2_pin_, LOW);

    now_speed_ = 0;
    // PWM 신호를 출력하여 모터 속도 조절
    analogWrite_custom(en_pin_, now_speed_);
}

void MyDCMotor::setSpeed(uint8_t speed){
    now_speed_ = map(abs(speed), 0, 255, 0, 255);
}

void MyDCMotor::run(uint8_t type){
    switch(type){
        case RELEASE:
            this->stop();
            break;
        case FORWARD:
            this->run_forward();
            break;
        case BACKWARD:
            this->run_backward();
            break;
        default:
            break;
    }
}
void MyDCMotor::slow(uint8_t plus){
  now_speed_ -= plus;
  if(now_speed_ < 130) now_speed_ = 130;
}
void MyDCMotor::fast(uint8_t plus){
  now_speed_ += plus;
  if(now_speed_ > 220) now_speed_ = 220;
}