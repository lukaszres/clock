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
void key_press(uint8_t *keylock, volatile uint8_t *KEY_PIN, uint8_t key_mask, void (*f)());
void displayMenu();

uint8_t keylock1;
uint8_t keylock2;
uint8_t keylock3;
float comparatorOverflows;
unsigned char tempSeconds;
unsigned char tempMinutes;
unsigned char tempHours;

int main(void) {
	valueToDisplay[0] = 10;
	valueToDisplay[1] = 10;
	valueToDisplay[2] = 10;
	valueToDisplay[3] = 10;
	_delay_ms(10); // oczekiwanie na ustalenie się stanu wysokiego na wejściu klawisza
	sei();
	timer1_init();
	multiplex_init();
	clock_init();

	PORTD |= KEY1 | KEY2 | KEY3;
	while (1) {
		key_press(&keylock2, &PIND, KEY2, displayMenu);
		key_press(&keylock3, &PIND, KEY3, resetTime);
	}
}

void enableDisplayClock() {
	displayClock = 1;
}

void addSecond() {
	increaseSeconds(&tempSeconds, &tempMinutes, &tempHours);
}

void minusSecond() {
	decreaseSeconds(&tempSeconds, &tempMinutes, &tempHours);
}

void displayMenu(void) {
	displayClock = !displayClock;
	tempSeconds = clockSeconds;
	tempMinutes = clockMinutes;
	tempHours = clockHours;
	while (!displayClock) {
		key_press(&keylock2, &PIND, KEY2, enableDisplayClock);
		key_press(&keylock3, &PIND, KEY3, minusSecond);
		key_press(&keylock1, &PIND, KEY1, addSecond);

		setValueToDisplay(tempMinutes, 0, 1);
		setValueToDisplay(tempSeconds, 2, 3);
	}
	clockSeconds = tempSeconds;
	clockMinutes = tempMinutes;
	clockHours = tempHours;
	setValueToDisplay(clockMinutes, 0, 1);
	setValueToDisplay(clockSeconds, 2, 3);
}

void key_press(uint8_t *keylock, volatile uint8_t *KEY_PIN, uint8_t key_mask, void (*f)()) {
	//reaguje na wcisniecie przycisku
	register uint8_t key_press = (*KEY_PIN & key_mask);
	if (!*keylock && !key_press) {
		*keylock = 1;
		f();
	} else if (*keylock && key_press) {
		(*keylock)++;
	}
}

ISR(TIMER1_COMPA_vect) {
//	interrupt every comparatorOverflows seconds
	display();	// displays valueToDisplay[]
	countClock(comparatorOverflows);
}

void timer1_init() {
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);	// set up timer with prescaler = 64 and CTC mode
														//Set prescaler to 64/1MHz : 1 click = 64us (assume 1MHz)
														//0,000064
	float timerClick = 0.000064;
	TIMSK |= (1 << OCIE1A);			// enable timer1 interrupts compare a match
	TCNT1 = 0;											// initialize counter
	OCR1A = 50;									// initialize compare value
	comparatorOverflows = timerClick * OCR1A;

}
