/*	Author: dpere048
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{locked, unlocked, release, wait} state;
unsigned char X;
unsigned char Y;
unsigned char M;
unsigned char Lock;
unsigned char tmpB;

void lock_Tick(){
	X = PINA&0x01;  //PA0
	Y = PINA&0x02; //PA1
	M  = PINA&0x03; //PA2 ..... PRESSING X AND THEN # UNLOCKS DOOR, SETS PB0 = 1
	Lock = PINA&0x80; //LOCKS FROM INSIDE
	switch(state){
		case locked:
			if(Lock){
				state = locked;
			}
			else if(!X && !Y && M && !Lock){
				state = wait;
			}
			else{
				state = locked;
			}
			break;
		case unlocked:
			if(!X && !Y && !M && Lock){
				state = locked;
			}
			else{
				state = unlocked;
			}
			break;
		case release:
			if(!X && !Y && !M && !Lock){
				state = release;
			}
			else if(!X && Y && !M && !Lock){
				state = unlocked;	
			}
			else{
				state = locked;
			}
			break;
		case wait:
			if(!X && !Y && M && !Lock){
				state = wait;
			}
			else if(!X && !Y && !M && !Lock){
				state = release;
			}
			else{	
				state = locked;
			}	
			break;
		   }
	switch(state){
		case locked:
			tmpB = 0x00;
			break;
		case unlocked:
			tmpB = 0x01;
			break;
		case release:
			break;
		case wait:
			break;
		}
	}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = locked;
    /* Insert your solution below */
    while (1) {
		lock_Tick();
		PORTB = tmpB;
    }
    return 0;
}
