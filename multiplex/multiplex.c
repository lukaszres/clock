/*
 * multiplex.c
 *
 *  Created on: Mar 12, 2022
 *      Author: lkre
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "multiplex.h"

const uint8_t cyfry[] PROGMEM = {
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

uint8_t cyfra[2];

ISR(TIMER0_OVF_vect) {
////	PORTC = PORTC ^ 1;
//	static uint8_t licznik;
//	ANODES_PORT = (ANODES_PORT | ANODE_MASK);
//	SEGMENT_PORT = pgm_read_byte(&cyfry[cyfra[licznik]]);
//
//	ANODES_PORT = (ANODES_PORT & ~ANODE_MASK) | (~(1 << licznik) & ANODE_MASK); //cykliczne przełączanie wyświetlaczy
//
//	licznik++;
//	if (licznik > 1) {
//		licznik = 0;
//	}
}

void display(void){
	SEGMENT_PORT = pgm_read_byte(&cyfry[cyfra[0]]);
}

void multiplex_init(void) {
	SEGMENT_DIRECTION = 0xff;
	SEGMENT_PORT = 0xff;

	ANODES_DIRECTION |= ANODE_1 | ANODE_2;
	ANODES_PORT |= ANODE_1 | ANODE_2;

	//Ustawienie TIMER0
//	TCCR0 |= (1<<WGM01) //tryb CTC

//	OCR0 = 215;

//	TIMSK = 0x01;   // maskowanie przerwań (odblokowanie generowania przerwania)
	TIMSK |= (1 << OCIE1A); //Zezwolenie na przerwania CompareMatch
	TCCR0 |= (1 << CS02) | (1 << CS00);	//preskaler 1024


//			MCUCR |= (1 << ISC11);
//	GICR |= (1 << INT0);
}
