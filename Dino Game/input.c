#include "header.h"

char button1 = 0;
char button2 = 0;
char button3 = 0;

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
}