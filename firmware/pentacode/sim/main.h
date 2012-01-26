#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>

#define LED_WIDTH	12
#define LED_HEIGHT	8

#define SIMULATOR

#define ATTRIBUTES	__attribute__((constructor));


typedef uint8_t (*tick_fun)(void);

void setLedXY(uint8_t x, uint8_t y, uint8_t brightness);
void registerAnimation(tick_fun tick, uint16_t t, uint16_t duration);

#endif
