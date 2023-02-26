#ifndef _MYDCMOTOR_H_
#define _MYDCMOTOR_H_

#include <stdint.h>

class MyDCMotor {
public:
    // constructor
    MyDCMotor(uint8_t in1_pin, uint8_t in2_pin, uint8_t pwm_pin);

    // motor control functions
    void run();
    void run_backward();
    void stop();
    void setSpeed(uint8_t speed);

private:
    uint8_t in1_pin_;   // 모터 방향 핀 1
    uint8_t in2_pin_;   // 모터 방향 핀 2
    uint8_t pwm_pin_;   // 모터 속도 제어 핀
    uint8_t now_speed_; // 현재 스피드
};

#endif