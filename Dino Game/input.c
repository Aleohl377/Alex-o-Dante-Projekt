#include "header.h"

char button1 = 0;
char button2 = 0;
char button3 = 0;

char sw1 = 0;
char sw2 = 0;
char sw3 = 0;
char sw4 = 0;

int getsw(void) {
	int SW = (PORTD >> 8) & 0x000F; // inputs för switches shiftad 8 till höger 
	return SW;
}
int getbtns(void) {
	int BTN = (PORTD >> 5) & 0x0007; // inputs för buttons shiftad 5 till höger
	return BTN;
}

void check_inputs(void)
{
	int button = getbtns();
  	button1 = (button & 1);
	button2 = (button & 2) >> 1;
	button3 = (button & 4) >> 2;

	int sw = getsw();
	sw1 = (sw & 1);
	sw2 = (sw & 2) >> 1;
	sw3 = (sw & 4) >> 2;
	sw4 = (sw & 8) >> 3;
}