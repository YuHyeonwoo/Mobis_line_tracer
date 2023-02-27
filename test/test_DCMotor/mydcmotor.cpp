#include "mydcmotor.h"

static uint8_t latch_state;

MyController::MyController(void) {
    TimerInitalized = false;
}

void MyController::enable(void) {
  pinMode_custom(MOTORLATCH, OUTPUT);
  pinMode_custom(MOTORENABLE, OUTPUT);
  pinMode_custom(MOTORDATA, OUTPUT);
  pinMode_custom(MOTORCLK, OUTPUT);

  latch_state = 0;

  latch_tx();  // "reset"

  digitalWrite(MOTORENABLE, LOW);
}


void MyController::latch_tx(void) {
  uint8_t i;

  //LATCH_PORT &= ~_BV(LATCH);
  digitalWrite_custom(MOTORLATCH, LOW);

  //SER_PORT &= ~_BV(SER);
  digitalWrite_custom(MOTORDATA, LOW);

  for (i=0; i<8; i++) {
    //CLK_PORT &= ~_BV(CLK);
    digitalWrite_custom(MOTORCLK, LOW);

    if (latch_state & _BV(7-i)) {
      //SER_PORT |= _BV(SER);
      digitalWrite_custom(MOTORDATA, HIGH);
    } else {
      //SER_PORT &= ~_BV(SER);
      digitalWrite_custom(MOTORDATA, LOW);
    }
    //CLK_PORT |= _BV(CLK);
    digitalWrite_custom(MOTORCLK, HIGH);
  }
  //LATCH_PORT |= _BV(LATCH);
  digitalWrite_custom(MOTORLATCH, HIGH);
}

static MyController MC;

inline void initPWM1(uint8_t freq) {
  TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21); // fast PWM, turn on oc2a
  TCCR2B = freq & 0x7;
  OCR2A = 0;
  pinMode_custom(11, OUTPUT);
}

inline void setPWM1(uint8_t s) {
  OCR2A = s;
}

inline void initPWM2(uint8_t freq) {
  TCCR2A |= _BV(COM2B1) | _BV(WGM20) | _BV(WGM21); // fast PWM, turn on oc2b
  TCCR2B = freq & 0x7;
  OCR2B = 0;
  pinMode_custom(3, OUTPUT);
}

inline void setPWM2(uint8_t s) {
  OCR2B = s;
}


MyDCMotor::MyDCMotor(uint8_t num, uint8_t freq) {
  motornum = num;
  pwmfreq = freq;

  MC.enable();

  switch (num) {
  case 1:
    latch_state &= ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B); // set both motor pins to 0
    MC.latch_tx();
    initPWM1(freq);
    break;
  case 2:
    latch_state &= ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B); // set both motor pins to 0
    MC.latch_tx();
    initPWM2(freq);
    break;
  }
}

void MyDCMotor::run(uint8_t cmd) {
  uint8_t a, b;
  switch (motornum) {
  case 1:
    a = MOTOR1_A; b = MOTOR1_B; break;
  case 2:
    a = MOTOR2_A; b = MOTOR2_B; break;
  default:
    return;
  }
  
  switch (cmd) {
  case FORWARD:
    latch_state |= _BV(a);
    latch_state &= ~_BV(b); 
    MC.latch_tx();
    break;
  case BACKWARD:
    latch_state &= ~_BV(a);
    latch_state |= _BV(b); 
    MC.latch_tx();
    break;
  case RELEASE:
    latch_state &= ~_BV(a);     // A and B both low
    latch_state &= ~_BV(b); 
    MC.latch_tx();
    break;
  }
}

void MyDCMotor::setSpeed(uint8_t speed) {
  switch (motornum) {
  case 1:
    setPWM1(speed); break;
  case 2:
    setPWM2(speed); break;
  }
}