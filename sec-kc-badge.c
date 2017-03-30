/*
 * sec_kc_badge.c
 *
 * Created: 5/3/2015 12:24:08 PM
 * Author:		Craig Berscheidt (craig.berscheidt@built-to-spec.com)
 * Compiler:	gcc-avr using AVR Studio 6
 * Target:		ATTINY85
 *
 * Program Command (avrdude using the USBtinyISP):
 * avrdude -c usbtiny -p t85 -U flash:w:"sec-kc-badge.hex"
 *
 * Peripherals Used:
 * None
 */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

enum pin_dirs {
	INPUT = 0,
	OUTPUT = 1
};

void set_gpio(int gpio, int value)
{
	if(value == 0)
		PORTB &= ~(_BV(gpio));
	else
		PORTB |= _BV(gpio);
}

void set_dir(int gpio, int dir)
{
	if (dir == INPUT)
		DDRB &= ~(_BV(gpio));
	else
		DDRB |= _BV(gpio);
}

void charlie_switch(int pin1, int pin2) {
	// Drive the first pin HIGH and the second one LOW
	set_dir(pin1, OUTPUT);
	set_dir(pin2, OUTPUT);
	set_gpio(pin1, 1);
	set_gpio(pin2, 0);
}

void charlie_plex(int led)
{
	//Make all pins inputs and disable pull ups
	for (int t = 2; t < 5; t++)
	{
		set_dir(t, INPUT);
		set_gpio(t, 0);
	}

	// turn on the appropriate LED
	switch (led) {
		case 0: charlie_switch(2, 3);
		break;
		case 1: charlie_switch(3, 4);
		break;
		case 2: charlie_switch(4, 3);
		break;
		case 3: charlie_switch(3, 2);
		break;
		case 4: charlie_switch(4, 2);
		break;
		case 5: charlie_switch(2, 4);
		break;
	}
}

int main(void)
{
	int i;

    while(1)
    {
		for (i=0; i<6; i++)
		{
			//turn on one LED
			charlie_plex(i);
			_delay_ms(150);
		}
    }
}
