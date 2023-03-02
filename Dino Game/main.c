/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"

/* ----- GAME STATES ----- */
int GAME_STATE = 0;
int GAME_MENU_STATE = 0;
int speed = 0;


int main(void) {

	hardware_init();
	display_init();

	init_data();

	title_screen();
	delay(1000);
	clear_text_buffer();
	//new life_init (Kanske inte funkar eftersom vi inte gjort krasch check ännu)
	//life_init();

	// Create player
	struct player p;
	p.x = 16;
	p.y = 16;
	p.width = 8;
	p.height = 8;
	p.graphic = dino;
	p.is_jumping = 0;
	p.jump_tick = 0;
	p.lifes = 3;

	/*
	struct enemy e1;
	p.x = 16;
	p.y = 16;
	p.width = 8;
	p.height = 8;
	p.graphic = enemy_graphic;
	*/

	spawn_enemies();

	//Create enemy?
	
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

			if(p.lifes == 3) PORTE = 0b0111;
			if(p.lifes == 2) PORTE = 0b0011;
			if(p.lifes == 1) PORTE = 0b0001;


			if (button1) p.x++;
			if (button2) p.x--;

			if (button3) p.is_jumping = 1;
			jump(&p);

			collision_detection(&p);
			
			update_display_bitmap(p.width, p.height, p.x, p.y, p.graphic);

			//update_display_bitmap(e1.width, e1.height, e1.x, e1.y, e1.graphic);

			update_enemies();
			draw_enemies();

			push_bitmap_to_display_buffer();

			update_display_buffer(ground);
			
			draw_display();

			clear_display_bitmap();

			//new Get_life check
			//Get_a_life();
		}
	}
	return 0;
}