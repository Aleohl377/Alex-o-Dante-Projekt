#include "header.h"





void jump(struct player *p)
{
	
    if(p->jump_tick < 6 && p->is_jumping == 1)
    {
        p->y -= 2;
    }
    else if (p->jump_tick >= 6 && p->jump_tick < 10 && p->is_jumping == 1)
    {
        p->y-= 1;
    }
    else if (p->jump_tick > 25 && p->jump_tick < 30 && p->is_jumping == 1)
    {
        p->y+= 1;
    }
    else if (p->jump_tick >= 30 && p->jump_tick <= 35 && p->is_jumping == 1)
    {
        p->y += 2;
    }
    else if (p->jump_tick > 35 && p->is_jumping == 1)
    {
        p->is_jumping = 0;
        p->jump_tick = 0;
        p->y = 16;
    }
    if (p->is_jumping == 1)
    {
        p->jump_tick++;
    }
    
}

void spawn_enemies(void)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        enemies[1].starting_position = 192 + (64 * i);
        enemies[i].x = enemies[i].starting_position;
        enemies[i].y = 16;
        enemies[i].width = 8;
        enemies[i].height = 8;
        enemies[i].graphic = enemy_graphic;
    }
}

void update_enemies(void)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        enemies[i].x -= (1*speed);
        
        if (enemies[i].x < -8)
        {
            enemies[i].x = (rand() % 1000 + 1) + 128;
        }
    }
}

void draw_enemies(void)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        if (enemies[i].x < 128)
            update_display_bitmap(enemies[i].width, enemies[i].height, enemies[i].x, enemies[i].y, enemies[i].graphic);
    }
}

void collision_detection(struct player *p)
{
    int i;

    // Loop through all enemies
    for (i = 0; i < 5; i++)
    {
        if (p->x < enemies[i].x + enemies[i].width &&
            p->x + p->width > enemies[i].x &&
            p->y < enemies[i].y + enemies[i].height &&
            p->height + p->y > enemies[i].y)
        {
            if (!is_colliding)
            {
                (*p).lifes--;
                is_colliding = 1;
                current_colliding_object = i;
            }  
        }
        else if (current_colliding_object == i)
        {
            is_colliding = 0;
        }
    }
}

/* This function is called repetitively from the main program */
void game_menu(void)
{
	if (button1 && GAME_MENU_STATE > 0)
	{
		GAME_MENU_STATE--;
	}
	if (button2 && GAME_MENU_STATE < 3)
	{
		GAME_MENU_STATE++;
	}
	
	switch (GAME_MENU_STATE)
	{
	case 0:
		display_string(0, "> Start");
		display_string(1, " Game Speed");
		display_string(2, " Highscore");
		display_string(3, " How to play");

		if (button3)
		{
			GAME_STATE = 1;
		}

		break;
	case 1:
		display_string(0, " Start");
		display_string(1, "> Game Speed");
		display_string(2, " Highscore");
		display_string(3, " How to play");

		if (button3)
		{
			display_string(0, "Switch 1 1x");
			display_string(1, "Switch 2 2x");
			display_string(2, "Switch 3 3x");
			display_string(3, "Switch 4 paus");
			delay(100);
			
			GAME_STATE = 0;
			
		}
		
		break;
	case 2:
		display_string(0, " Start");
		display_string(1, " Game Speed");
		display_string(2, "> Highscore");
		display_string(3, " How to play");

		if (button3)
		{
            char text[9];
            convert_integer_to_chars(top_highscore, text);
            text[8] = '\0';

			display_string(0, " TOP SCORE:");
		    display_string(1, text);
		    display_string(2, "");
		    display_string(3, "");
		}

		break;
	case 3:
		display_string(0, " Start");
		display_string(1, " Game Speed");
		display_string(2, " Highscore");
		display_string(3, "> How to play");

		if (button3)
		{
			display_string(0, "Jump over enemys");
			display_string(1, "3 lives");
			display_string(2, "shown on leds");
			display_string(3, "");
			
			GAME_STATE = 0;
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


void check_game_over(void)
{
    clear_display_bitmap();
    display_string(0, "Game over");
    display_string(1, "LOSER!");
    display_string(2, "HAHA!");
    display_string(3, "");
    display_update();
    delay(800);
    display_black();
    display_string(0, "Restarting...");
    delay(800);
    GAME_STATE = 0;
    spawn_enemies();
}


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

void game_speed(void)
{
	if (sw1)
	{
		speed = 2;
	}
	if (sw2)
	{
		speed = 3;
	}
	if (sw3)
	{
		speed = 4;
	}
	if (sw4)
	{
		speed = 0;
	}
}

void dead_anime(struct player *p)
{
	if (dead_tick < 5 && GAME_STATE == 2)
	{
		p->y -=2;
		p->x -=1;
	}
	else if (dead_tick >= 5 && dead_tick < 12 && GAME_STATE == 2)
	{
		p->y +=3;
		p->x -=1;
	}
	
}