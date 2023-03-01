#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"



void jump(struct player *p)
{
    if(p->jump_tick < 4 && p->is_jumping == 1)
    {
        p->y -= 2;
    }
    else if (p->jump_tick >= 4 && p->jump_tick < 11 && p->is_jumping == 1)
    {
        p->y--;
    }
    else if (p->jump_tick > 13 && p->jump_tick < 15 && p->is_jumping == 1)
    {
        p->y++;
    }
    else if (p->jump_tick >= 15 && p->jump_tick <= 20 && p->is_jumping == 1)
    {
        p->y += 2;
    }
    else if (p->jump_tick > 20 && p->is_jumping == 1)
    {
        p->is_jumping = 0;
        p->jump_tick = -1;
    }
	else if (p->is_jumping == 0)
	{
		p->jump_tick = 0;
	}
    p->jump_tick++;
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


/*_____DANTE NILSSON din jävel titta på denna kod______*/
//void life_init (void)
//{
//	TRISE &= ~0xff;  /* set 8 lsb to outputs*/
//	PORTE = 0x07;	/*set value of LEDs to 7 (turn on 3 first leds)*/

//	int player_life = 2; // For LEDs, POW of 2 is the first life
//	int hit = 0;
//}

/*--Check life and display on LEDSs--*/
/*void Get_a_life(void)
{
	int life;
	int life_new;
	// hit variabeln är variabeln som ändras om krasch (kan ändras)
	if (hit == 1);
	{
		// player_life är variabeln som minskar leds  
		life = simple_pow(2, player_life);
		life_new = ~(life);
		PORTE = PORTE & life_new;

		player_life--;
		hit == 0;
	}
}*/