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
volatile int* PORTEs = (volatile int*)0xbf886110; //skapa pointer till portE
volatile int* TRISEs = (volatile int*)0xbf886100;

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
	TRISEs &= ~0xff;  /* set 8 lsb to outputs*/
  // 
	PORTEs = 0;	/*set value of LEDs to 0*/
  //
	TRISD |= 0xfe0;	/* set bits 11 till 5*/
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  int button = getbtns();
	int switches = getsw();

	if (button & 1)
  {
		mytime &= 0xff0f; // rensar andra visaren  00:X0
		mytime = (switches << 4) | mytime;  // ersätter minuterna med input från switches
	}

	if (button & 2) 
  {
		mytime &= 0xf0ff; //rensar tredje visaren  0X:00
		mytime = (switches << 8) | mytime;
	}

	if (button & 4) 
  {
		mytime &= 0x0fff; //rensar fjärde visaren  X0:00
		mytime = (switches << 12) | mytime;
	}

  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  PORTEs += 1;	/* addera med 1 till PORTE efter varje tick*/
  display_image(96, icon);
}