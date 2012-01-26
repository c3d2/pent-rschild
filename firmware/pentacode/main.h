#ifndef _MAIN_H
#define _MAIN_H

#include <inttypes.h>

void setLedXY(uint8_t,uint8_t,uint8_t); // x , y , brightness
void setLedAll(uint8_t); // brightness

#define LED_WIDTH   12
#define LED_HEIGHT  8

#define ATTRIBUTES	__attribute__ ((naked, used, section (".init8")));

void registerAnimation(uint8_t (*)(void),uint16_t,uint16_t);

#define MAX_NUMBER_OF_ANIMATIONS 10

#endif
