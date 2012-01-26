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

void init_scroll(void) ATTRIBUTES;


static const uint8_t pic[32] =
	{ 0x18 , 0x24 , 0x42 , 0x99 , 0x24 , 0x42 , 0x99 , 0x24 ,
	0x42   , 0x81 , 0x0  , 0xC0 , 0x3C , 0x3  , 0x0  , 0x81 ,
	0x42   , 0x24 , 0x99 , 0x42 , 0x24 , 0x18 , 0x0  , 0x0  ,
	0      , 0    , 0    , 0    , 0    , 0    , 0    , 0     };

static uint8_t tick_scroll(void);

void init_scroll(void)
{
	registerAnimation(tick_scroll, 150, 48);
}

uint8_t tick_scroll()
{
	static uint8_t cnt = 0;
	for (uint8_t i = 0; i < 12; i++) {
		for(uint8_t y = 0; y < 8 ; y++) {
			setLedXY(i,y, ((pic[(i+cnt) & 0x1f])&(1<<y))?1:0 );
		}
	}
	cnt++;
	return 0;
}
