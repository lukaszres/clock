/*
 * clock.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */

#include <stdint.h>
#include <stdbool.h>
#include "clock.h"
#include "../multiplex/multiplex.h"

struct Time clockTime;
uint16_t ticks;
bool displayClock = true;
void increaseSeconds(struct Time *time);
void resetTime();

void clock_init() {
	resetTime();
}

void resetTime() {
	clockTime.seconds = 60;
	clockTime.minutes = 60;
	clockTime.hours = 24;
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

		increaseSeconds(&clockTime);

		if (displayClock) {
			setValueToDisplay(clockTime.minutes, 0, 1);
			setValueToDisplay(clockTime.seconds, 2, 3);
		}
	}
}

void increaseSeconds(struct Time *time) {
	time->seconds++;
	if (time->seconds >= 60) {
		time->seconds = 0;
		(time->minutes)++;
		if (time->minutes >= 60) {
			time->minutes = 0;
			(time->hours)++;
			if (time->hours >= 24) {
				time->hours = 0;
			}
		}
	}
}

void decreaseSeconds(struct Time *time) {
	if (time->seconds > 0) {
		(time->seconds)--;
	} else {
		time->seconds = 59;
		if (time->minutes > 0) {
			(time->minutes)--;
		} else {
			time->minutes = 59;
			if (time->hours > 0) {
				(time->hours)--;
			} else {
				time->hours = 23;
			}
		}
	}
}
