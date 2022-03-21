/*
 * clock.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */
#include <stdint.h>
#include "../multiplex/multiplex.h"
#include <stdbool.h>

unsigned char seconds;
unsigned char minutes;
uint16_t ticks = 312;
bool displayClock = true;

void setValueToDisplay(uint8_t liczba) {
	if (liczba == 0) {
		valueToDisplay[2] = 0;
		valueToDisplay[3] = 0;
	} else {
		uint8_t tens = liczba / 10;
		uint8_t units = liczba - tens * 10;
		valueToDisplay[2] = tens;
		valueToDisplay[3] = units;
	}
}

void setMinutesToDisplay(uint8_t liczba) {
	if (liczba == 0) {
		valueToDisplay[0] = 0;
		valueToDisplay[1] = 0;
	} else {
		uint8_t tens = liczba / 10;
		uint8_t units = liczba - tens * 10;
		valueToDisplay[0] = tens;
		valueToDisplay[1] = units;
	}
}

void countClock() {
	/*
	 Timer2 overflows every 0,0032 (when OCR1A = 50)
	 Every 312 times the time passed is equal to 0,9984 (almost 1 sec)
	 */
	ticks++;
	if (ticks >= 312) {
		/*      One second has passed   */
		ticks = 0;

		seconds++;
		if (seconds >= 60) {
			seconds = 0;
			minutes++;
			if (minutes >= 60) {
				minutes = 0;
			}
		}
		if (displayClock) {
			setValueToDisplay(seconds);
			setMinutesToDisplay(minutes);
		}
	}
}
