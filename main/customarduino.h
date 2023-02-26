#ifndef __CUSTOMARDUINO_H__
#define __CUSTOMARDUINO_H__

#include <arduino.h>

volatile uint8_t *portToDDR(uint8_t port);
volatile uint8_t *portToPORT(uint8_t port);
volatile uint8_t *portToPIN(uint8_t port);


void pinMode_custom(uint8_t pin, uint8_t mode);
void digitalWrite_custom(uint8_t pin, uint8_t mode);
int digitalRead_custom(uint8_t pin);

void analogWrite_custom(uint8_t pin, uint8_t mode); // 아날로그 출력이 가능한 핀만 가능함 
int analogRead_custom(uint8_t pin);
void tone_custom(uint8_t pin, uint16_t frequency, uint16_t duration);

#endif