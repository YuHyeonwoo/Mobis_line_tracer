#ifndef _TRACEMODEL_H_
#define _TRACEMODEL_H_
#include <AFMotor.h>
#include "customarduino.h"

#define DELTA 80

class TraceModel{
private:
  int speed_fro;
  int speed_cur;
  int line_r = 14;
  int line_l = 19;
  AF_DCMotor* pm1;
  AF_DCMotor* pm2;

  int stat[2];
  int speedArr[2];

  int isChange(int type, int speed);
  void Move(char cmd);
  void Speed(int type, int speed);
public:
  TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin);
  void Go();
  int Slow();
  int Fast();
  void Stop();
};

#endif