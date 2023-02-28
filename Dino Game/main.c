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

/* ----- I/O ----- */
void check_inputs(void);
char button1 = 0;
char button2 = 0;
char button3 = 0;

/* ----- Player Positions ----- */
int px = 16;
int py = 16;

int jump_counter = 0;
int jump_true = 0;


void game_menu(void);



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

	while (1)
	{
		check_inputs();

		if (GAME_STATE == 0)
		{
			game_menu();
		}
		else if (GAME_STATE == 1)
		{

			if (button1) px++;
			if (button2) px--;
			if (button3) jump_true = 1;
			
			update_display_bitmap(8, 8, px, py, dino);

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

void check_inputs(void)
{
	int button = getbtns();
  	button1 = (button & 1);
	button2 = (button & 2) >> 1;
	button3 = (button & 4) >> 2;
	delay(10000);
}

void jump()
{
	if(jump_counter < 4 && jump_true == 1)
	{
		py -= 2;
	}
	else if (jump_counter >= 4 && jump_counter < 11 && jump_true == 1)
	{
		py--;
	}
	else if (jump_counter > 13 && jump_counter < 15 && jump_true == 1)
	{
		py++;
	}
	else if (jump_counter >= 15 && jump_counter <= 20 && jump_true == 1)
	{
		py += 2;
	}
	else if (jump_counter > 20 && jump_true == 1)
	{
		jump_true = 0;
		jump_counter = -1;
	}
	jump_counter++;
}