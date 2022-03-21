/*tens
 *
 * multiplex.c
 *
 *  Created on: Mar 12, 2022
 *      Author: lkre
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "multiplex.h"

const uint8_t digits[] PROGMEM = { (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F), 			//0
		(SEG_B | SEG_C),											//1
		(SEG_A | SEG_B | SEG_D | SEG_E | SEG_G),					//2
		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_G),					//3
		(SEG_B | SEG_C | SEG_F | SEG_G),							//4
		(SEG_A | SEG_C | SEG_D | SEG_F | SEG_G),					//5
		(SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),			//6
		(SEG_A | SEG_B | SEG_C | SEG_F),							//7
		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G),	//8
		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G),			//9
		0 };
uint8_t valueToDisplay[4];

void multiplex_init(void) {
	SEGMENT_DIRECTION = 0xff;
	SEGMENT_PORT = 0xff;

	ANODES_DIRECTION |= ANODE_1 | ANODE_2 | ANODE_3 | ANODE_4;	// set anodes to exit
	ANODES_PORT &= ANODE_1 | ANODE_2 | ANODE_3 | ANODE_4;		// clear displays
}

void display(void) {
	static uint8_t displayNumber;
	ANODES_PORT = (ANODES_PORT & ANODE_MASK);		//clear displays
	SEGMENT_PORT = pgm_read_byte(&digits[valueToDisplay[displayNumber]]);

	ANODES_PORT = (ANODES_PORT & ~ANODE_MASK) | ((1 << displayNumber) & ANODE_MASK); //cyclic switching of displays

	displayNumber++;
	if (displayNumber > 3) {
		displayNumber = 0;
	}
}

void setValueToDisplay(uint8_t liczba, uint8_t firstNumber, uint8_t secondNumber) {
	if (liczba == 0) {
		valueToDisplay[firstNumber] = 0;
		valueToDisplay[secondNumber] = 0;
	} else {
		uint8_t tens = liczba / 10;
		uint8_t units = liczba - tens * 10;
		valueToDisplay[firstNumber] = tens;
		valueToDisplay[secondNumber] = units;
	}
}
