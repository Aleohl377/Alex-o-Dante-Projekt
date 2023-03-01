#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#include "header.h"
#include "display.h"



/*
    What exactly does this stuff do?
*/
#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)


/*  num32asc
    Helper function, local to this file.
    Converts a number to hexadecimal ASCII digits. 
*/
static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}


/*
SPI2STAT<3>: (SPITBE) Transmit Buffer Empty Status bit.
  1 = SPIxTXB is empty
  0 = SPIxTXB is not empty
SPI2STAT<0>: (SPIRBF) Receive Buffer Full Status bit.
  1 = Receive Buffer, SPIxRXB is full
  0 = Receive Buffer, SPIxRXB is not full
*/
/* spi_send_recv: Prepares two chunks for sending data first and then
receiving an answer, queues a transfer and waits for
it to complete.  This is not a full-duplex operation.*/
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));  // Waits for the transmit buffer to be empty
	SPI2BUF = data;             // Push data to buffer
	while(!(SPI2STAT & 1));     // Waits for the buffer to be full
	return SPI2BUF;             // Return buffer
}


/*  display_init

*/
void display_init(void) {
	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}


/* display_debug
   A function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/   
void display_debug( volatile int * const addr )
{
  display_string( 1, "Addr" );
  display_string( 2, "Data" );
  num32asc( &textbuffer[1][6], (int) addr );
  num32asc( &textbuffer[2][6], *addr );
  display_update();
}


/*  display_string

*/
void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}


/*  display_image

*/
void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32*4; j++)
			spi_send_recv(~data[i*32*4 + j]);
	}
}

void display_small_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 1; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32/4; j++)
			spi_send_recv(~data[i*32/4 + j]);
	}
}

/*  display_update
    Prints textbuffer to display.
*/
void display_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}


/* ----- NEW STUFF ----- */

/*  display_black
    Simple for loop that resets the display.
*/
void display_black(void)
{
	int i;
	for (i = 0; i < 512; i++)
	{
		display_buffer[i] = 0;
	}
}


void display_white(void)
{
	int x, y;
	for (x = 0; x < 128; x++)
	{
		for (y = 0; y < 32; y++)
		{
			display[y][x] = 1;
		}
	}
}


void clear_text_buffer(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 16; j++)
		{
			textbuffer[i][j] = 0;
		}
	}

	display_update();
}


void ground_init(void)
{
	display_image(0,ground);
}


/* update_display_buffer

*/

/*
update_display_bitmap
	@brief: 
	@author:
	@params:
		width:
		height: 
		x: 
		y: 
		data: 
	@return: Void
*/
void update_display_bitmap(int width, int height, int x, int y, const uint8_t *data)
{
	// Bound checking
	if (width > 128) width = 128;
	else if (width < 0) width = 0;

	if (height > 32) height = 32;
	else if (height < 0) height = 0;

	if ((x + width) >= 0 && (y + height) >= 0)
	{
		int i, j;
		int c = 0;

		for (i = y; i < (y + height); i++)
		{
			for (j = x; j < (x + width); j++)
			{
				// Only update the display bitmap if the pixel is inside the display bounds
				if (j < 128 && i < 32 && j >= 0 && j >= 0)
				{
					display[i][j] = data[c];
				}
				c++;
			}
		}
	}
}


/* update_display_buffer
	Only works with [512] arrays.
	(Will be used for the floor)
*/
void update_display_buffer(const uint8_t *data)
{
	int page, row;

	for (page = 0; page < 4; page++)
	{
		for (row = 0; row < 128; row++)
		{
			display_buffer[row + (128 * page)] |= data[row + (128 * page)];
		}
	}
}


int simple_pow(int x, int y)
{
	if ( x == 0 ) return 0;
	if ( y == 0 ) return 1;
	if ( y == 1 ) return x;

	int i, m = x;
	for (i = 1; i < y; i++)
		x *= m;
	
	return x;
}

void push_bitmap_to_display_buffer(void)
{
	int acc = 0;
	int i, j, k;

	for (k = 0; k < 4; k++)
	{
		for (i = 0; i < 128; i++)
		{
			for (j = 0; j < 8; j++)
			{
				acc += display[j + (8 * k)][i] * simple_pow(2, j);
			}

			display_buffer[i + (128 * k)] = acc;
			acc = 0;
		}
	}	
}


void clear_display_bitmap(void)
{
	int col, row;

	for (col = 0; col < 32; col++)
	{
		for (row = 0; row < 128; row++)
		{
			display[col][row] = 0;
		}
	}
}


/*

Display resolution: 128 x 32 px

The display memory can hold max 512 bytes.
The display memory is organized as four pages of 128 bytes each.
Each memory page corresponds to an 8-pixel-high stripe across the display.
The least significant bit in a display byte is the top most pixel, and the most significant bit the bottom most pixel.
The first byte in the page corresponds to the left most pixels on the display and the last byte the right most pixels.

Display buffer has to be reduced from 4096 bytes to 512 bytes before being pushed to display memory.



*/
void draw_display(void)
{
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		/* Set the page address */
		spi_send_recv(0x22);	// Set page command
		spi_send_recv(i);		// page number (0-3)
		
		/* Start at the left column */
		spi_send_recv(0x0); 	//set low nybble of column
		spi_send_recv(0x10);	//set high nybble of column
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(display_buffer[(i * 128) + j]);
	}
}