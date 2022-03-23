/*
 * clock.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */
#include <stdint.h>
#include "../multiplex/multiplex.h"
#include <stdbool.h>

unsigned char clockSeconds;
unsigned char clockMinutes;
unsigned char clockHours;
uint16_t ticks;
bool displayClock = true;
void increaseSeconds(unsigned char *seconds, unsigned char *minutes, unsigned char *hours);
void resetTime();

void clock_init() {
	resetTime();
}

void resetTime() {
	clockSeconds = 60;
	clockMinutes = 60;
	clockHours = 24;
	ticks = 312;
}

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

		increaseSeconds(&clockSeconds, &clockMinutes, &clockHours);

		if (displayClock) {
			setValueToDisplay(clockMinutes, 0, 1);
			setValueToDisplay(clockSeconds, 2, 3);
		}
	}
}

void increaseSeconds(unsigned char *seconds, unsigned char *minutes, unsigned char *hours) {
	(*seconds)++;
	if (*seconds >= 60) {
		*seconds = 0;
		(*minutes)++;
		if (*minutes >= 60) {
			*minutes = 0;
			(*hours)++;
			if (*hours >= 24) {
				hours = 0;
			}
		}
	}
}

void decreaseSeconds(unsigned char *seconds, unsigned char *minutes, unsigned char *hours) {
	if (*seconds > 0) {
		(*seconds)--;
	} else {
		*seconds = 59;
		if (*minutes > 0) {
			(*minutes)--;
		} else {
			*minutes = 59;
			if (*hours > 0) {
				(*hours)--;
			} else {
				*hours = 23;
			}
		}
	}
}
