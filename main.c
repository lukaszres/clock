/*
 * main.c
 *
 *  Created on: Mar 11, 2022
 *      Author: lkre
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "multiplex/multiplex.h"

#define DISP_1 0b00000001
#define DISP_2 0b00000010
#define MULTIPLEXER PORTC

int main(void) {
	multiplex_init();
	cyfra[0] = 9;
	cyfra[1] = 3;
//
//	sei();

//	SEGMENT_PORT &= (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G);
//			ANODES_PORT &= (ANODE_1 | ANODE_2);

	while (1) {
		ANODES_PORT = (ANODES_PORT & ~ANODE_MASK) | (ANODE_1 & ANODE_MASK); //cykliczne przełączanie wyświetlaczy
		for (int i = 10; i >= 0; i--) {
			cyfra[0] = i;
			display();
			_delay_ms(1000);
		}
		ANODES_PORT = (ANODES_PORT & ~ANODE_MASK) | (ANODE_2 & ANODE_MASK); //cykliczne przełączanie wyświetlaczy
		for (int i = 10; i >= 0; i--) {
			cyfra[0] = i;
			display();
			_delay_ms(1000);
		}
	}
}

