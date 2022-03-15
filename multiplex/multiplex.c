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

const uint8_t digits[] PROGMEM = {
		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F), 			//0
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
uint8_t valueToDisplay[2];


void multiplex_init(void) {
	SEGMENT_DIRECTION = 0xff;
	SEGMENT_PORT = 0xff;

	ANODES_DIRECTION |= ANODE_1 | ANODE_2;
	ANODES_PORT |= ANODE_1 | ANODE_2;
}

void display(void) {
	static uint8_t displayNumber;
	ANODES_PORT = (ANODES_PORT | ANODE_MASK);
	SEGMENT_PORT = pgm_read_byte(&digits[valueToDisplay[displayNumber]]);

	ANODES_PORT = (ANODES_PORT & ~ANODE_MASK) | (~(1 << displayNumber) & ANODE_MASK); //cyclic switching of displays

	displayNumber++;
	if (displayNumber > 1) {
		displayNumber = 0;
	}
}
