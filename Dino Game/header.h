/* 
   header.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING
*/


/* ----- FUNCTIONS (functions.c) ----- */
char * itoaconv( int num );
void tick( unsigned int * timep );
void quicksleep(int cycles);
void delay(int);
void hardware_init(void);



/* ----- DATA (data.c) ----- */
void init_data(void);

extern const uint8_t const font[128*8];   // (Lab code) Font
extern char textbuffer[4][16];            // (Lab code) Textbuffer, 4 lines, 16 letters max on each line

extern uint8_t display[32][128];          // Display bitmap 128 x 32 px
extern uint8_t display_buffer[128*4];     // Display buffer, each element corresponds to 8 pixels
extern uint8_t ground[128*4];             // Graphic: Ground
extern const uint8_t const dino[8*8];     // Graphic: Dino
extern const uint8_t const enemy[8*8];    // Graphic: Enemy



/* ----- INPUT/OUTPUT (input.c) ----- */
void check_inputs(void);
int getbtns(void);
int getsw(void);

extern char button1;
extern char button2;
extern char button3;



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
};

void game_menu(void);
void title_screen(void);





