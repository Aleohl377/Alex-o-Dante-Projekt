/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"
#include "display.h"


//int mytime = 0x5957;
//volatile int* PORTEs = (volatile int*)0xbf886110; //skapa pointer till portE
//volatile int* TRISEs = (volatile int*)0xbf886100;

int GAME_STATE = 0;
int GAME_MENU_STATE = 0;


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
  	delay(100);

	if (button & 1 && GAME_MENU_STATE > 0)
	{
		GAME_MENU_STATE--;
	}
	if (button & 2 && GAME_MENU_STATE < 2)
	{
		GAME_MENU_STATE++;
	}
	
	switch (GAME_MENU_STATE)
	{
	case 0:
		display_string(0, "> Start");
		display_string(1, " By group 50");
		display_string(2, " Game speed");
		display_string(3, "");

		if (button & 4)
		{
			GAME_STATE = 1;
		}

		break;
	case 1:
		display_string(0, " Start");
		display_string(1, "> By group 50");
		display_string(2, " Game speed");
		display_string(3, "");

		if (button & 4)
		{
			GAME_STATE = 1;
		}
		
		break;
	case 2:
		display_string(0, " Start");
		display_string(1, " By group 50");
		display_string(2, "> Game speed");
		display_string(3, "");

		if (button & 4)
		{
			GAME_STATE = 1;
		}

		break;
	default:
		break;
	}

	display_update();
}

int main(void) {

	/* ----- INIT STUFF -----*/
	/*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	/* Our code*/
	// changed strings
	/* --------- END ---------*/
	
	display_init();
	display_string(0, "Dino jump!");
	display_string(1, "By group 50");
	display_string(2, "");
	display_string(3, "Welcome!");
	//spi_send_recv(255);
	display_update();
	delay(3000);
	
	// New set of strings to get black screen
	display_string(0, "");
	display_string(1, "");
	display_string(2, "");
	display_string(3, "");
	display_update();

	//Game_init();
	
	labinit(); /* Do any lab-specific initialization */

	init_data();

	int x = 16;

	while (1)
	{

		if (GAME_STATE == 0)
		{
			labwork();
		}
		else if (GAME_STATE == 1)
		{
			int button = getbtns();

			if (button & 1) x++;
			if (button & 2) x--;
			
			//update_display_bitmap(8, 8, 0, 0, dino2);
			//update_display_bitmap(8, 8, 8, 8, dino2);
			update_display_bitmap(8, 8, x, 16, dino2);

			//display_white();

			push_bitmap_to_display_buffer();

			update_display_buffer(ground);
			
			draw_display();

			clear_display_bitmap();
		}
	}
	return 0;
}
