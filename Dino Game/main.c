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


/* ----- Player Positions ----- */
struct player
{
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	const uint8_t *graphic;
};


void game_menu(void);
void title_screen(void);



int main(void) {

	hardware_init();
	display_init();

	init_data();

	title_screen();
	delay(1000);
	clear_text_buffer();

	// Create player
	struct player p;
	p.x = 16;
	p.y = 16;
	p.width = 8;
	p.height = 8;
	p.graphic = dino;

	while (1)
	{
		check_inputs();

		if (GAME_STATE == 0)
		{
			game_menu();
			delay(100);
		}
		else if (GAME_STATE == 1)
		{

			if (button1) p.x++;
			if (button2) p.x--;
			
			update_display_bitmap(p.width, p.height, p.x, p.y, p.graphic);

			push_bitmap_to_display_buffer();

			update_display_buffer(ground);
			
			draw_display();

			clear_display_bitmap();
		}
	}
	return 0;
}

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
		display_string(1, " By group 50");
		display_string(2, " Game speed");
		display_string(3, "");

		if (button3)
		{
			GAME_STATE = 1;
		}

		break;
	case 1:
		display_string(0, " Start");
		display_string(1, "> By group 50");
		display_string(2, " Game speed");
		display_string(3, "");

		if (button3)
		{
			GAME_STATE = 1;
		}
		
		break;
	case 2:
		display_string(0, " Start");
		display_string(1, " By group 50");
		display_string(2, "> Game speed");
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