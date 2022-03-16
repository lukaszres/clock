/*
 * main.c
 *
 *  Created on: Mar 11, 2022
 *      Author: lkre
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "multiplex/multiplex.h"
#include "clock/clock.h"

#define KEY1 (1<<PD0)
#define KEY2 (1<<PD1)
#define KEY3 (1<<PD2)

void timer1_init();
void key_press(uint8_t *keylock, volatile uint8_t *KEY_PIN, uint8_t key_mask);

uint8_t keylock1;

int main(void) {
	valueToDisplay[0] = 10;
	valueToDisplay[1] = 10;
	_delay_ms(10); // oczekiwanie na ustalenie się stanu wysokiego na wejściu klawisza
	sei();
	timer1_init();
	multiplex_init();

	PORTD |= KEY1 | KEY2 | KEY3;
	while (1) {
		key_press(&keylock1, &PIND, KEY2);
	}
}

void key_press(uint8_t *keylock, volatile uint8_t *KEY_PIN, uint8_t key_mask) {
	//reaguje na wcisniecie przycisku
	register uint8_t key_press = (*KEY_PIN & key_mask);
	if (!*keylock && !key_press) {
		*keylock = 1;
		displayClock = !displayClock;
		if (!displayClock) {
			setValueToDisplay(88);
		} else {
			setValueToDisplay(seconds);
		}
	} else if (*keylock && key_press) {
		(*keylock)++;
	}
}

ISR(TIMER1_COMPA_vect) {
	display();	// displays actual value of cyfra[]

	/*
	 Timer2 overflows every 0,0128
	 Every 78 times the time passed is equal to 0,998s4 (almost 1 sec)
	 */
	countClock();
}

void timer1_init() {
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);	// set up timer with prescaler = 64 and CTC mode
														//Set prescalar to 64/1MHz : 1 click = 64us (assume 1MHz)
														//0,000064
	TIMSK |= (1 << OCIE1A);			// enable timer1 interrupts compare a match
	TCNT1 = 0;											// initialize counter
	OCR1A = 200;									// initialize compare value

}
