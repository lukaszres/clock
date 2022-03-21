/*
 * multiplex.h
 *
 *  Created on: Mar 12, 2022
 *      Author: lkre
 */

#ifndef MULTIPLEX_MULTIPLEX_H_
#define MULTIPLEX_MULTIPLEX_H_

//Definition of ports
#define SEGMENT_PORT			PORTB
#define SEGMENT_DIRECTION		DDRB

#define ANODES_PORT				PORTC
#define ANODES_DIRECTION		DDRC

// Definition of bits
#define ANODE_1 (1<<PC0)
#define ANODE_2 (1<<PC1)
#define ANODE_3 (1<<PC2)
#define ANODE_4 (1<<PC3)
#define ANODE_MASK (ANODE_1 | ANODE_2 | ANODE_3 | ANODE_4)

#define SEG_A (1<<6)
#define SEG_B (1<<7)
#define SEG_C (1<<2)
#define SEG_D (1<<1)
#define SEG_E (1<<0)
#define SEG_F (1<<5)
#define SEG_G (1<<4)
#define SEG_DP (1<<3)

void multiplex_init(void);
void display(void);
void setValueToDisplay(uint8_t liczba, uint8_t firstNumber, uint8_t secondNumber);

extern uint8_t valueToDisplay[4];

#endif /* MULTIPLEX_MULTIPLEX_H_ */
