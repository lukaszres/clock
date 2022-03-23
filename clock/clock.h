/*
 * clock.h
 *
 *  Created on: Mar 15, 2022
 *      Author: lkre
 */

#ifndef CLOCK_CLOCK_H_
#define CLOCK_CLOCK_H_
#include <stdbool.h>

extern unsigned char clockSeconds;
extern unsigned char clockMinutes;
extern unsigned char clockHours;
extern bool displayClock;

void countClock(float comparatorOverflows);
void resetTime();
void increaseSeconds(unsigned char *seconds, unsigned char *minutes, unsigned char *hours);
void decreaseSeconds(unsigned char *seconds, unsigned char *minutes, unsigned char *hours);
void clock_init();

#endif /* CLOCK_CLOCK_H_ */
