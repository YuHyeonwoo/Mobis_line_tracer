#ifndef __CUSTOMARDUINO_H__
#define __CUSTOMARDUINO_H__

volatile uint8_t *portToDDR(uint8_t port);
volatile uint8_t *portToPORT(uint8_t port);
volatile uint8_t *portToPIN(uint8_t port);


void pinMode_custom(uint8_t pin, uint8_t mode);
void digitalWrite_custom(uint8_t pin, uint8_t mode);
int digitalRead_custom(uint8_t pin);

void analogWrite_custom(uint8_t pin, uint8_t mode); // 9번, 10번에 핀에 대한 출력만 
int analogRead_custom(uint8_t pin);

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


// 아날로그 입력 값을 읽어오는 함수
int analogRead_custom(uint8_t pin) {
  // 핀 번호에 따른 ADC 핀 설정
  uint8_t adc_pin;
  
  // A0 는 14번핀
  if (pin >= 14) pin -= 14;  
 
  // ADMUX 레지스터 설정 (ADC는 오른쪽 정렬임)
  ADMUX = (1 << 6) | (pin & 0x07);
  
  // ADC 변환 시작
  ADCSRA |= (1 << 6);
  
  // 변환 완료를 기다림
  while(ADCSRA & (1 << 6));
  
  // 결과값 계산, 오른쪽 정렬이므로 ADCH를 8bit shift
  int adc_value = ADCL | (ADCH << 8);
  
  return adc_value;
}



void analogWrite_custom(uint8_t pin, int value) {
  // 핀 번호를 Timer/Counter 번호로 변환
  uint8_t timer;
  switch(pin) {
    case 3: timer = 8; break;
    case 5: timer = 2; break;
    case 6: timer = 1; break;
    case 9: timer = 3; break;
    case 10: timer = 4; break;
    case 11: timer = 7; break;
    default: return;   // 잘못된 핀 번호 입력
  }

  switch(timer){
    case 1:
      TCCR0A |= (1 << 7);
      OCR0A = value;	
      break;
    case 2:
      TCCR0A |= (1 << 5);
      OCR0B = value;
      break;
    case 3:
      TCCR1A |= (1 << 7);
      OCR1A = value;
      break;
    case 4:
      TCCR1A |= (1 << 5);
			OCR1B = value;
      break;
    case 7:
      TCCR2A |= (1 << 7);
      OCR2A = value;
      break;
    case 8:
      TCCR2A |= (1 << 5);
      OCR2B = value;
      break;
  }
}

#endif