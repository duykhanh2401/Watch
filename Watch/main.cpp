#define F_CPU 8000000UL
#include <avr/io.h>
#include "myLCD.h"
#include <avr/interrupt.h>
#include <stdlib.h>
int gio=21,phut=35,giay=00;
long dem=0, day=5,month=8,year=2020;

int main(void)
{
	init_LCD();
	clr_LCD();
	TCCR0=0x03;
	TCNT0=130;
	TIMSK=0x01;
	sei();
	
    while (1) 
    {	
			time(gio,phut,giay);
			move_LCD(2,1);
			date(day,month,year,dem);
			if(dem>=1000)
			{
				giay++;
				if(giay<60)
				{
					time(gio,phut,giay);
				}
				else
				{
					giay=0;
					time(gio,phut,giay);
					phut++;
					if(phut<60)
					{
						time(gio,phut,giay);
					}
					else
					{
						phut=0;
						time(gio,phut,giay);
						gio++;
						if(gio<24)
						{
							time(gio,phut,giay);
						}
						else
						{
							gio=0;
							time(gio,phut,giay);
						}
					}
				}
				time(gio,phut,giay);
				dem=0;
				if(giay==0) clr_LCD();

			}
	}
}

ISR(TIMER0_OVF_vect)
{
	TCNT0=130;
	dem++;
}
