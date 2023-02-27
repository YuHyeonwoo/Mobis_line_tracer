#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "customarduino.h"

static int Tones[7] = {261, 294, 330, 349, 392, 440, 494};                   // 도, 레, 미, 파, 솔, 라, 시

class Obstacle{
  int Buzzer_Pin;
  int IR_Sensor_Pin;
public:
  void pinSet(int Buzzer_Pin, int IR_Sensor_Pin); // 부저번호, 핀번호
  int checkObstacle(); // 장애물이 인식되면 1, 아니면 0 출력
  void stopSound(); // 경고음을 울림
};



#endif