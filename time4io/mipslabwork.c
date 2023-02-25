/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
//volatile int* PORTEs = (volatile int*)0xbf886110; //skapa pointer till portE
//volatile int* TRISEs = (volatile int*)0xbf886100;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // LEDS
	TRISE &= ~0xff;  /* set 8 lsb to outputs*/
  // 
	PORTE = 0;	/*set value of LEDs to 0*/
  //
	TRISD |= 0xfe0;	/* set bits 11 till 5*/
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  int button = getbtns();
	int switches = getsw();
  delay(1000);
  display_init();
	display_string(0, "> Start");
	display_string(1, " Settings");
	display_string(2, " Game Speed");
  display_string(3, "");
	display_update();

	if (button & 1)
  {
    display_init();
	delay(1000);
	display_string(0, " Start");
	display_string(1, "> By group 50");
	display_string(2, " Game speed");
  display_string(3, "");
	
	}

	if (button & 2) 
  {
    display_init();
  delay(1000);
	display_string(0, " Start");
	display_string(1, " By group 50");
	display_string(2, "> Game speed");
  display_string(3, "");
	
	}

	if (button & 4) 
  {
    display_init();
  delay(1000);
	display_string(0, " Start");
	display_string(1, "> By group 50");
	display_string(2, " Game speed");
  display_string(3, "");
	
	}

  //delay( 1000 );
  //time2string( textstring, mytime );
  //display_string( 3, textstring );
  display_update();
  //tick( &mytime );
  //PORTE += 1;	/* addera med 1 till PORTE efter varje tick*/
  //display_image(96, icon);
}