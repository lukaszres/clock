/*
 * clock.h
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */

#ifndef CLOCK_CLOCK_H_
#define CLOCK_CLOCK_H_
#include <stdbool.h>

extern unsigned char seconds;
extern unsigned char minutes;
extern bool displayClock;

void countClock(float comparatorOverflows);
void resetTime();

#endif /* CLOCK_CLOCK_H_ */
