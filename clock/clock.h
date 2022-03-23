/*
 * clock.h
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */

#ifndef CLOCK_CLOCK_H_
#define CLOCK_CLOCK_H_
#include <stdbool.h>

struct Time {
	unsigned char seconds;
	unsigned char minutes;
	unsigned char hours;
};

extern bool displayClock;
extern struct Time clockTime;

void countClock(float comparatorOverflows);
void resetTime();
void increaseSeconds(struct Time *time);
void decreaseSeconds(struct Time *time);
void clock_init();

#endif /* CLOCK_CLOCK_H_ */
