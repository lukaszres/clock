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
void displayMenuSetTime();

uint8_t keylock1;
uint8_t keylock2;
uint8_t keylock3;
float comparatorOverflows;
struct Time tempTime;

int main(void) {
	_delay_ms(10); // oczekiwanie na ustalenie się stanu wysokiego na wejściu klawisza
	sei();
	timer1_init();
	multiplex_init();
	displayOff();
	clock_init();

	PORTD |= KEY1 | KEY2 | KEY3;
	while (1) {
		key_press(&keylock2, &PIND, KEY2, displayMenuSetTime);
		key_press(&keylock3, &PIND, KEY3, resetTime);
	}
}

void enableDisplayClock() {
	displayClock = 1;
}

void addSecond() {
	increaseSeconds(&tempTime);
}

void minusSecond() {
	decreaseSeconds(&tempTime);
}

void displayTempTime() {
	setValueToDisplay(tempTime.minutes, 0, 1);
	setValueToDisplay(tempTime.seconds, 2, 3);
}

void displayMenuSetTime(void) {
	displayClock = !displayClock;
	displayOff();
	_delay_ms(1000);
	tempTime = clockTime;
	while (!displayClock) {
		key_press(&keylock2, &PIND, KEY2, enableDisplayClock);
		key_press(&keylock3, &PIND, KEY3, minusSecond);
		key_press(&keylock1, &PIND, KEY1, addSecond);
		displayTempTime();
	}
	clockTime = tempTime;
//	displayTempTime();
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
