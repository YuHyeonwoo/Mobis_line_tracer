#ifndef __CUSTOMARDUINO_H__
#define __CUSTOMARDUINO_H__

volatile uint8_t *portToDDR(uint8_t port);
volatile uint8_t *portToPORT(uint8_t port);
volatile uint8_t *portToPIN(uint8_t port);


void pinMode_custom(uint8_t pin, uint8_t mode);
void digitalWrite_custom(uint8_t pin, uint8_t mode);
int digitalRead_custom(uint8_t pin);

volatile uint8_t *portToDDR(uint8_t port) {
  switch (port) {
    case 0:
      return &DDRD;
    case 1:
      return &DDRB;
    case 2:
      return &DDRC;
    default:
      return NULL;
  }
}

volatile uint8_t *portToPORT(uint8_t port) {
  switch (port) {
    case 0:
      return &PORTD;
    case 1:
      return &PORTB;
    case 2:
      return &PORTC;
    default:
      return NULL;
  }
}
volatile uint8_t *portToPIN(uint8_t port) {
  switch (port) {
    case 0:
      return &PIND;
    case 1:
      return &PINB;
    case 2:
      return &PINC;
    default:
      return NULL;
  }
}


void pinMode_custom(uint8_t pin, uint8_t mode) {
  uint8_t port = pin / 8;           // 핀이 속한 포트 번호 계산
  if(pin > 13) port = 2;
  uint8_t bit = pin % 8;           // 핀이 속한 비트 번호 계산
  if(pin > 13) bit = pin - 14;
  
  volatile uint8_t *ddr = portToDDR(port);  // 해당 포트의 DDR 레지스터 주소 가져오기

  if (mode == OUTPUT) {
    *ddr |= 1 << bit;            // 해당 비트를 1으로 설정하여 출력으로 설정
  } else {
    *ddr &= ~(1 << bit);             // 해당 비트를 0으로 설정하여 입력으로 설정
  }
}

void digitalWrite_custom(uint8_t pin, uint8_t mode) {
  uint8_t port = pin / 8;           // 핀이 속한 포트 번호 계산
  if(pin > 13) port = 2;
  uint8_t bit = pin % 8;           // 핀이 속한 비트 번호 계산
  if(pin > 13) bit = pin - 14;
  
  volatile uint8_t *PORT = portToPORT(port);  // 해당 포트의 PORT 레지스터 주소 가져오기

  if (mode == OUTPUT) {
    *PORT |= 1 << bit;            // 해당 비트를 1으로 설정하여 출력으로 설정
  } else {
    *PORT &= ~(1 << bit);             // 해당 비트를 0으로 설정하여 입력으로 설정
  }
}

int digitalRead_custom(uint8_t pin){
  uint8_t port = pin / 8;           // 핀이 속한 포트 번호 계산
  if(pin > 13) port = 2;
  uint8_t bit = pin % 8;           // 핀이 속한 비트 번호 계산
  if(pin > 13) bit = pin - 14;
  
  volatile uint8_t *PIN = portToPIN(port);  // 해당 포트의 PIN 레지스터 주소 가져오기

  if (*PIN & (1 << bit)) {
    return HIGH;
  } else {
    return LOW;
  }

}



#endif