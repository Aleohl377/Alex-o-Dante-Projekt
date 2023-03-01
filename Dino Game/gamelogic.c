#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"
#include "display.h"


/* This function is called repetitively from the main program */
void game_menu(void)
{
	if (button1 && GAME_MENU_STATE > 0)
	{
		GAME_MENU_STATE--;
	}
	if (button2 && GAME_MENU_STATE < 2)
	{
		GAME_MENU_STATE++;
	}
	
	switch (GAME_MENU_STATE)
	{
	case 0:
		display_string(0, "> Start");
		display_string(1, " Game Speed");
		display_string(2, " Highscore");
		display_string(3, "");

		if (button3)
		{
			GAME_STATE = 1;
		}

		break;
	case 1:
		display_string(0, " Start");
		display_string(1, "> Game Speed");
		display_string(2, " Highscore");
		display_string(3, "");

		if (button3)
		{
			GAME_STATE = 1;
		}
		
		break;
	case 2:
		display_string(0, " Start");
		display_string(1, " Game Speed");
		display_string(2, "> Highscore");
		display_string(3, "");

		if (button3)
		{
			GAME_STATE = 1;
		}

		break;
	default:
		break;
	}

	display_update();
}

void title_screen(void)
{
	/* ----- TITLE SCREEN ----- */
	display_string(0, "Dino jump!");
	display_string(1, "By group 50");
	display_string(2, "");
	display_string(3, "Welcome!");
	display_update();
}