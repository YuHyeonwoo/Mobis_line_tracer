#include "customarduino.h"


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


void tone_custom(uint8_t pin, unsigned int frequency, unsigned long duration) {
// 타이머2 레지스터의 초기화
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  
  // 타이머2 레지스터의 설정
  TCCR2A |= (1 << WGM21) | (1 << COM2B0);
  TCCR2B |= (1 << CS21);
  
  // 타이머2 레지스터의 출력 비율 계산
  int prescaler = 64;
  int ocrValue = F_CPU / (prescaler * frequency) - 1;
  OCR2A = ocrValue;
  
  // tone 출력을 위한 디지털 핀 설정
  pinMode_custom(pin, OUTPUT);
  digitalWrite_custom(pin, 0);
  
  // tone 출력 시작
  long elapsed_time = 0;
  while (elapsed_time < duration*1000) {
    digitalWrite_custom(pin, 1);
    delayMicroseconds(ocrValue);
    digitalWrite_custom(pin, 0);
    delayMicroseconds(ocrValue);
    elapsed_time += (ocrValue * 2);
  }
  
  // tone 출력 종료 및 초기화
  digitalWrite_custom(pin, 0);
  TCCR2A = 0;
  TCCR2B = 0;
}