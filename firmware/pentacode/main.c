#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


#include "main.h"
#include "pins.h"

//these variables are used by the timer intr
static uint8_t row_step = 0;
static uint8_t rowbyte_portc[12] = {~0,~0,~0,~0,~0 ,~0 ,~1,~2,~4,~8,~16,~32};
static uint8_t rowbyte_portb[12] = {~1,~2,~4,~8,~16,~32,~0,~0,~0,~0,~0 ,~0 };
static volatile uint8_t colbyte_portd[12]={
							0,0,0,0,0,0,0,0,0,0,0,0
						};

ISR (TIMER1_OVF_vect)
{
	row_step++;
	if(row_step==12)
	{
		row_step = 0;
	}

	PORTD = 0;

	PORTC = rowbyte_portc[row_step];
	PORTB = rowbyte_portb[row_step];

	PORTD = colbyte_portd[row_step];

}


int main(void)
{
	ROW0_DDR |= (1<<ROW0_PIN);
	ROW1_DDR |= (1<<ROW1_PIN);
	ROW2_DDR |= (1<<ROW2_PIN);
	ROW3_DDR |= (1<<ROW3_PIN);
	ROW4_DDR |= (1<<ROW4_PIN);
	ROW5_DDR |= (1<<ROW5_PIN);
	ROW6_DDR |= (1<<ROW6_PIN);
	ROW7_DDR |= (1<<ROW7_PIN);

	COL0_DDR |= (1<<COL0_PIN);
	COL1_DDR |= (1<<COL1_PIN);
	COL2_DDR |= (1<<COL2_PIN);
	COL3_DDR |= (1<<COL3_PIN);
	COL4_DDR |= (1<<COL4_PIN);
	COL5_DDR |= (1<<COL5_PIN);
	COL6_DDR |= (1<<COL6_PIN);
	COL7_DDR |= (1<<COL7_PIN);
	COL8_DDR |= (1<<COL8_PIN);
	COL9_DDR |= (1<<COL9_PIN);
	COL10_DDR |= (1<<COL10_PIN);
	COL11_DDR |= (1<<COL11_PIN);


	ROW0_OFF;
	ROW1_OFF;
	ROW2_OFF;
	ROW3_OFF;
	ROW4_OFF;
	ROW5_OFF;
	ROW6_OFF;
	ROW7_OFF;

	// only one col at a time !!
	COL0_OFF;
	COL1_OFF;
	COL2_OFF;
	COL3_OFF;
	COL4_OFF;
	COL5_OFF;
	COL6_OFF;
	COL7_OFF;
	COL8_OFF;
	COL9_OFF;
	COL10_OFF;
	COL11_OFF;
		

	TCCR1A |= (1<<WGM10)|(1<<WGM11);
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);
	TIMSK1 |= (1<<TOIE1);
	OCR1A = 0xff;
	
	sei();
	
	setLedAll(0);

	uint8_t x,y;

	while(1)
	{
		for(x = 0; x < 12;x++)
		{
			for(y = 0;y < 8;y++)
			{
				setLedAll(0);
				setLedXY(x,y,1);
				_delay_ms(10);
			}
		}
	}

}


void setLedXY(uint8_t x,uint8_t y, uint8_t brightness)
{
	if(brightness == 0)
	{
		colbyte_portd[x] &= ~(1<<y);
	}
	else
	{
		colbyte_portd[x] |= (1<<y);
	}
}

void setLedAll(uint8_t brightness)
{
	for(uint8_t i = 0;i < 12;i++)
	{
		colbyte_portd[i] = brightness * 0xff;
	}
}

