// #ifndef _TRACEMODEL_H_
// #define _TRACEMODEL_H_
// #include <SoftwareSerial.h>
// #include <AFMotor.h>

// class TraceModel{
// private:
//   int speed_fro;
//   int speed_cur;
//   int line_r = A0;
//   int line_l = A5;
//   AF_DCMotor* pm1;
//   AF_DCMotor* pm2;

//   int stat[2];
//   int speedArr[2];

//   int isChange(int type, int speed);
//   void Move(char cmd);
//   void Speed(int type, int speed);
// public:
//   TraceModel(int sp_f, int sp_c, int motor1_pin, int motor2_pin);
//   void Go();
// };

// #endif