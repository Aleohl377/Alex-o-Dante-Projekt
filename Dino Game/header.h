/* 
   header.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING
*/
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <stdlib.h>


/* ----- Display (display.c) ----- */
uint8_t spi_send_recv(uint8_t data);               // (Lab code)
void display_init(void);                           // (Lab code)
void display_debug( volatile int * const addr );   // (Lab code)
void display_update(void);                         // (Lab code)
void display_string(int line, char *s);            // (Lab code)
void display_image(int x, const uint8_t *data);    // (Lab code)

/* ----- NEW STUFF ----- */
void update_display_bitmap(int width, int height, int x, int y, const uint8_t *data);
void push_bitmap_to_display_buffer(void);
void update_display_buffer(const uint8_t *data);
void clear_display_bitmap(void);
void draw_display(void);
void clear_text_buffer(void);

void display_white(void);
void display_black(void);
void ground_init(void);

int simple_pow(int x, int y);

void Game_init(void);
void Game_loop(void);



/* ----- FUNCTIONS (functions.c) ----- */
char * itoaconv( int num );               // (Lab code)
void tick( unsigned int * timep );        // (Lab code)
void quicksleep(int cycles);              // (Lab code)
void delay(int);                          // (Lab code)

void hardware_init(void);



/* ----- DATA (data.c) ----- */
void init_data(void);

extern const uint8_t const font[128*8];   // (Lab code) Font
extern char textbuffer[4][16];            // (Lab code) Textbuffer, 4 lines, 16 letters max on each line

extern uint8_t display[32][128];          // Display bitmap 128 x 32 px
extern uint8_t display_buffer[128*4];     // Display buffer, each element corresponds to 8 pixels
extern uint8_t ground[128*4];             // Graphic: Ground
extern const uint8_t const dino[8*8];     // Graphic: Dino
extern const uint8_t const player_2[8*8]; // Graphic: Player 2
extern const uint8_t const enemy_graphic[8*8];    // Graphic: Enemy



/* ----- INPUT/OUTPUT (input.c) ----- */
void check_inputs(void);
int getbtns(void);         // (Lab code)
int getsw(void);           // (Lab code)

extern char button1;
extern char button2;
extern char button3;

extern char sw1;
extern char sw2;
extern char sw3;
extern char sw4;

/* ----- GAME LOGIC (gamelogic.c) ----- */
int GAME_STATE;
int GAME_MENU_STATE;

struct player
{
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	const uint8_t *graphic;
   uint8_t is_jumping;
   uint8_t jump_tick;
   uint8_t lifes;
   int highscore;
};

struct enemy
{
	int x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	const uint8_t *graphic;
};

struct enemy enemies[5];
void spawn_enemies(void);
void update_enemies(void);
void draw_enemies(void);

void jump(struct player *p);

int is_colliding;
int current_colliding_object;
void collision_detection(struct player *p);

void game_menu(void);
void title_screen(void);
void check_game_over(void);

extern int speed;





