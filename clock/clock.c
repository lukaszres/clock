/*
 * clock.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */
#include <stdint.h>
#include "../multiplex/multiplex.h"

unsigned char seconds;
unsigned char ticks = 78;

void setValueToDisplay(uint8_t liczba) {
	if (liczba == 0) {
		valueToDisplay[1] = 0;
		valueToDisplay[0] = 0;
	} else {
		uint8_t tens = liczba / 10;
		uint8_t units = liczba - tens * 10;
		valueToDisplay[1] = tens;
		valueToDisplay[0] = units;
	}
}

void countClock() {
	ticks++;
	if (ticks >= 78) {
		/*      One second has passed   */
		ticks = 0;

		seconds++;
		if (seconds >= 60) {
			seconds = 0;
		}
		setValueToDisplay(seconds);
	}
}
