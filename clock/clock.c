/*
 * clock.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */
#include <stdint.h>
#include "../multiplex/multiplex.h"
#include <stdbool.h>

unsigned char seconds = 60;
unsigned char minutes = 60;
uint16_t ticks = 312;
bool displayClock = true;

void countClock(float comparatorOverflows) {
	/*
	 Timer2 overflows every 0,0032 (when OCR1A = 50)
	 Every 312 times the time passed is equal to 0,9984 (almost 1 sec)
	 */
	uint16_t maxTick = 1 / comparatorOverflows;
	ticks++;
	if (ticks >= maxTick) {
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
			setValueToDisplay(minutes, 0, 1);
			setValueToDisplay(seconds, 2, 3);
		}
	}
}

void resetTime() {
	seconds = 60;
	minutes = 60;
	ticks = 312;
}
