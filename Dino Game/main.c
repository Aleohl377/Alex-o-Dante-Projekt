/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"
#include "display.h"

/* ----- GAME STATES ----- */
int GAME_STATE = 0;
int GAME_MENU_STATE = 0;


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* This function is called repetitively from the main program */
void game_menu( void )
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

	hardware_init();
	display_init();

	/* ----- TITLE SCREEN ----- */
	display_string(0, "Dino jump!");
	display_string(1, "By group 50");
	display_string(2, "");
	display_string(3, "Welcome!");
	display_update();
	delay(3000);
	
	// Empty string buffer
	display_string(0, "");
	display_string(1, "");
	display_string(2, "");
	display_string(3, "");
	display_update();

	//Game_init();

	init_data();

	int x = 16;

	while (1)
	{

		if (GAME_STATE == 0)
		{
			game_menu();
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
