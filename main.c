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

void timer1_init();

int main(void) {
	valueToDisplay[0] = 10;
	valueToDisplay[1] = 10;
	sei();
	timer1_init();
	multiplex_init();

	while (1) {
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
