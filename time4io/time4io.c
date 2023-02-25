#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int getsw(void) {
	int SW = (PORTD >> 8) & 0x000F; // inputs för switches shiftad 8 till höger 
	return SW;
}
int getbtns(void) {
	int BTN = (PORTD >> 5) & 0x0007; // inputs för buttons shiftad 5 till höger
	return BTN;
}