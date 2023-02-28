/* 
   header.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING
*/


char * itoaconv( int num );
void tick( unsigned int * timep );


void init_data(void);
void hardware_init(void);


void game_menu(void);


void delay(int cycles);
int getbtns(void);
int getsw(void);


/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/*          NEW STUFF         */
/* Declare bitmap array containing the whole display */
extern uint8_t display[32][128];
/* Display buffer ready to be sent to display memory */
extern uint8_t display_buffer[128 * 4];
/* bitmap array containing grafical objekt (ground)*/
extern uint8_t ground[128*4];
/* dino player */
extern const uint8_t const dino[8*8];
/* white box */
extern const uint8_t const white_box[8*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];





