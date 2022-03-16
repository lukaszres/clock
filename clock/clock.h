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
extern bool displayClock;

void countClock(void);
void setValueToDisplay(uint8_t liczba);

#endif /* CLOCK_CLOCK_H_ */
