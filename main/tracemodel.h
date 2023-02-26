#ifndef _TRACEMODEL_H_
#define _TRACEMODEL_H_
#include "mydcmotor.h"

class TraceModel{
private:
  int speed_fro;
  int speed_cur;
  int line_r = A0;
  int line_l = A5;
  MyDCMotor* pm1;
  MyDCMotor* pm2;

  int stat[2];
  int speedArr[2];

  int isChange(int type, int speed);
  void Move(char cmd);
  void Speed(int type, int speed);
public:
  TraceModel(int motor1_pwm, int motor1_in1, int motor1_in2, int motor2_pwm, int motor2_in1, int motor2_in2);
  void Go();
};

#endif