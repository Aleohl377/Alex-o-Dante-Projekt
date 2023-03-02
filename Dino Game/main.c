/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include "header.h"
#include <stddef.h>
void *stdin = NULL;
void *stdout = NULL;
void *stderr = NULL;

/* ----- GAME STATES ----- */
int GAME_STATE = 0;
int GAME_MENU_STATE = 0;
int speed = 1;
int dead_tick = 0;


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
	p.highscore = 0;

	int jump_cooldown = 1;

	spawn_enemies();
	
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
			collision_detection(&p);

			if(p.lifes == 3) PORTE = 0b0111;
			if(p.lifes == 2) PORTE = 0b0011;
			if(p.lifes == 1) PORTE = 0b0001;
			if(p.lifes == 0) PORTE = 0b0000;

			if (p.lifes <= 0)
			{
				GAME_STATE = 2;
			}
			else
			{
				if (button1) p.x++;
				if (button2) p.x--;

				if (button3) p.is_jumping = 1;
				jump(&p);

				update_display_bitmap(p.width, p.height, p.x, p.y, p.graphic);

				game_speed();
				update_enemies();
				draw_enemies();

				push_bitmap_to_display_buffer();

				update_display_buffer(3, ground);
				
				draw_display();

				if (jump_cooldown) delay(500);
				jump_cooldown = 0;

				if (button3) p.is_jumping = 1;
				jump(&p);

				clear_display_bitmap();

				p.highscore++;
			}
		}
		else if (GAME_STATE == 2)
		{
			dead_anime(&p);
			dead_tick++;
			if (dead_tick > 20)
			{
				
				p.lifes = 3;
				p.y = 16;
				p.x = 16;
				GAME_STATE = 0;
				dead_tick = 0;
				p.jump_tick = 0;

				if (p.highscore > top_highscore) top_highscore = p.highscore;

				spawn_enemies();
				check_game_over();
			}
			update_display_bitmap(p.width, p.height, p.x, p.y, p.graphic);

			push_bitmap_to_display_buffer();

			draw_display();

			clear_display_bitmap();

			jump_cooldown = 1;
		}
	}
	return 0;
}