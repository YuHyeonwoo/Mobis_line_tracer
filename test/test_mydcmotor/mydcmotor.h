#ifndef _AFMotor_h_
#define _AFMotor_h_

#include <inttypes.h>
#include <avr/io.h>
#include "customarduino.h"

#define DC_MOTOR_PWM_RATE _BV(CS01)
// Bit positions in the 74HCT595 shift register output
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// Constants that the user passes in to the stepper calls
#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3
#define MICROSTEP 4

// Arduino pin names for interface to 74HCT595 latch
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

class MyController
{
  public:
    MyController(void);
    void enable(void);
    friend class MyDCMotor;
    void latch_tx(void);
    uint8_t TimerInitalized;
};

class MyDCMotor
{
 public:
  MyDCMotor(uint8_t motornum, uint8_t freq = DC_MOTOR_PWM_RATE);
  void run(uint8_t);
  void setSpeed(uint8_t);
  void slow(uint8_t);
  void fast(uint8_t);
  uint8_t now_speed;

 private:
  uint8_t motornum, pwmfreq;
};

#endif