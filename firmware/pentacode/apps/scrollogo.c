/*
 * =====================================================================================
 *
 *       Filename:  scollogo.c
 *
 *    Description: <<</>> scroller. simulator unsafe
 *
 *        Version:  1.0
 *        Created:  26.01.2012 03:42:52
 *       Revision:  none
 *       Compiler:  avg-gcc
 *
 *         Author:  _john (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <main.h>

static const uint8_t pic[24] =
    { 0x18, 0x24, 0x42, 0x99, 0x24, 0x42, 0x99, 0x24, 0x42, 0x81, 0x0, 0xC0,
0x3C, 0x3, 0x0, 0x81, 0x42, 0x24, 0x99, 0x42, 0x24, 0x18, 0x0, 0x0 };

static uint8_t tick_scroll(void);
extern uint8_t *colbyte_portd;

void init_random(void)
{
	registerAnimation(tick_scroll, 50, 48);
}

uint8_t tick_scroll()
{
	static uint8_t cnt = 0;
	for (uint8_t i = 0; i < 12; i++) {
		colbyte_portd[i] = pic[(i + cnt) % 12];
	}
	cnt++;
	return 0;
}
