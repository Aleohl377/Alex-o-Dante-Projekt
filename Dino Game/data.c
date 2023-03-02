#include "header.h"

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

// 4 lines, max 16 letters on each line
char textbuffer[4][16];

uint8_t display[32][128];
uint8_t display_buffer[128*4];
uint8_t ground[128];

void init_data(void)
{
	int i, j;

	/* ----- Display ----- */
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 128; j++)
		{
			display[i][j] = 0;
		}
	}

	/* ----- Display Buffer ----- */
	for (i = 0; i < (128 * 4); i++)
	{
		display_buffer[i] = 0;
	}

	/* ----- Ground ----- */
	for (j = 0; j < 128; j++)
	{
		int temp = rand() % 100 + 1;
		if (temp <= 50) ground[j] = 170;
		else if (temp > 50) ground[j] = 85;
	}

}

const uint8_t const dino[] = 
{
	0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 1, 0, 1, 1, 1, 0,
	0, 0, 1, 1, 1, 1, 1, 0,
	1, 0, 0, 1, 1, 0, 0, 0,

	1, 0, 1, 1, 1, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	0, 0, 1, 0, 0, 1, 0, 0,
	0, 0, 1, 1, 0, 1, 1, 0,
};

const uint8_t const player_2[] = 
{
	0, 0, 0, 1, 1, 1, 0, 0,
	0, 0, 1, 0, 0, 0, 1, 0,
	0, 1, 1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 0, 0, 1, 1,

	0, 0, 1, 0, 0, 0, 1, 1,
	0, 0, 1, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 1, 0, 1, 0,
	0, 0, 0, 1, 0, 1, 0, 0,
};

const uint8_t const enemy_graphic[] = 
{
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    1, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 1,

    1, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 1, 0,
    1, 1, 1, 1, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 1, 1,
};


/* ----- LAB CODE ----- */
const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,			// 0
	0, 0, 0, 0, 0, 0, 0, 0,			// 1
	0, 0, 0, 0, 0, 0, 0, 0,			// 2
	0, 0, 0, 0, 0, 0, 0, 0,			// 3
	0, 0, 0, 0, 0, 0, 0, 0,			// 4
	0, 0, 0, 0, 0, 0, 0, 0,			// 5
	0, 0, 0, 0, 0, 0, 0, 0,			// 6
	0, 0, 0, 0, 0, 0, 0, 0,			// 7
	0, 0, 0, 0, 0, 0, 0, 0,			// 8
	0, 0, 0, 0, 0, 0, 0, 0,			// 9
	0, 0, 0, 0, 0, 0, 0, 0,			// 10
	0, 0, 0, 0, 0, 0, 0, 0,			// 11
	0, 0, 0, 0, 0, 0, 0, 0,			// 12
	0, 0, 0, 0, 0, 0, 0, 0,			// 13
	0, 0, 0, 0, 0, 0, 0, 0,			// 14
	0, 0, 0, 0, 0, 0, 0, 0,			// 15
	0, 0, 0, 0, 0, 0, 0, 0,			// 16
	0, 0, 0, 0, 0, 0, 0, 0,			// 17
	0, 0, 0, 0, 0, 0, 0, 0,			// 18
	0, 0, 0, 0, 0, 0, 0, 0,			// 19
	0, 0, 0, 0, 0, 0, 0, 0,			// 20
	0, 0, 0, 0, 0, 0, 0, 0,			// 21
	0, 0, 0, 0, 0, 0, 0, 0,			// 22
	0, 0, 0, 0, 0, 0, 0, 0,			// 23
	0, 0, 0, 0, 0, 0, 0, 0,			// 24
	0, 0, 0, 0, 0, 0, 0, 0,			// 25
	0, 0, 0, 0, 0, 0, 0, 0,			// 26
	0, 0, 0, 0, 0, 0, 0, 0,			// 27
	0, 0, 0, 0, 0, 0, 0, 0,			// 28
	0, 0, 0, 0, 0, 0, 0, 0,			// 29
	0, 0, 0, 0, 0, 0, 0, 0,			// 30
	0, 0, 0, 0, 0, 0, 0, 0,			// 31
	0, 0, 0, 0, 0, 0, 0, 0,			// 32 : (space)
	0, 0, 0, 94, 0, 0, 0, 0,		// 33 : !
	0, 0, 4, 3, 4, 3, 0, 0,			// 34 : "
	0, 36, 126, 36, 36, 126, 36, 0,	// 35 : #
	0, 36, 74, 255, 82, 36, 0, 0,	// 36 : $
	0, 70, 38, 16, 8, 100, 98, 0,	// 37 : %
	0, 52, 74, 74, 52, 32, 80, 0,	// 38 : &
	0, 0, 0, 4, 3, 0, 0, 0,			// 39 : '
	0, 0, 0, 126, 129, 0, 0, 0,		// 40 : (
	0, 0, 0, 129, 126, 0, 0, 0,		// 41 : )
	0, 42, 28, 62, 28, 42, 0, 0,	// 42 : *
	0, 8, 8, 62, 8, 8, 0, 0,		// 43 : +
	0, 0, 0, 128, 96, 0, 0, 0,		// 44 : ´
	0, 8, 8, 8, 8, 8, 0, 0,			// 45 : -
	0, 0, 0, 0, 96, 0, 0, 0,		// 46 : .
	0, 64, 32, 16, 8, 4, 2, 0,		// 47 : /
	0, 62, 65, 73, 65, 62, 0, 0,	// 48 : 0
	0, 0, 66, 127, 64, 0, 0, 0,		// 49 : 1
	0, 0, 98, 81, 73, 70, 0, 0,		// 50 : 2
	0, 0, 34, 73, 73, 54, 0, 0,		// 51 : 3
	0, 0, 14, 8, 127, 8, 0, 0,		// 52 : 4
	0, 0, 35, 69, 69, 57, 0, 0,		// 53 : 5
	0, 0, 62, 73, 73, 50, 0, 0,		// 54 : 6
	0, 0, 1, 97, 25, 7, 0, 0,		// 55 : 7
	0, 0, 54, 73, 73, 54, 0, 0,		// 56 : 8
	0, 0, 6, 9, 9, 126, 0, 0,		// 57 : 9
	0, 0, 0, 102, 0, 0, 0, 0,		// 58 : :
	0, 0, 128, 102, 0, 0, 0, 0,		// 59 : ;
	0, 0, 8, 20, 34, 65, 0, 0,		// 60 : <
	0, 0, 20, 20, 20, 20, 0, 0,		// 61 : =
	0, 0, 65, 34, 20, 8, 0, 0,		// 62 : >
	0, 2, 1, 81, 9, 6, 0, 0,		// 63 : ?
	0, 28, 34, 89, 89, 82, 12, 0,	// 64 : @
	0, 0, 126, 9, 9, 126, 0, 0,		// 65 : A
	0, 0, 127, 73, 73, 54, 0, 0,	// 66 : B
	0, 0, 62, 65, 65, 34, 0, 0,		// 67 : C
	0, 0, 127, 65, 65, 62, 0, 0,	// 68 : D
	0, 0, 127, 73, 73, 65, 0, 0,	// 69 : E
	0, 0, 127, 9, 9, 1, 0, 0,		// 70 : F
	0, 0, 62, 65, 81, 50, 0, 0,		// 71 : G
	0, 0, 127, 8, 8, 127, 0, 0,		// 72 : H
	0, 0, 65, 127, 65, 0, 0, 0,		// 73 : I
	0, 0, 32, 64, 64, 63, 0, 0,		// 74 : J
	0, 0, 127, 8, 20, 99, 0, 0,		// 75 : K
	0, 0, 127, 64, 64, 64, 0, 0,	// 76 : L
	0, 127, 2, 4, 2, 127, 0, 0,		// 77 : M
	0, 127, 6, 8, 48, 127, 0, 0,	// 78 : N
	0, 0, 62, 65, 65, 62, 0, 0,		// 79 : O
	0, 0, 127, 9, 9, 6, 0, 0,		// 80 : P
	0, 0, 62, 65, 97, 126, 64, 0,	// 81 : Q
	0, 0, 127, 9, 9, 118, 0, 0,		// 82 : R
	0, 0, 38, 73, 73, 50, 0, 0,		// 83 : S
	0, 1, 1, 127, 1, 1, 0, 0,		// 84 : T
	0, 0, 63, 64, 64, 63, 0, 0,		// 85 : U
	0, 31, 32, 64, 32, 31, 0, 0,	// 86 : V
	0, 63, 64, 48, 64, 63, 0, 0,	// 87 : W
	0, 0, 119, 8, 8, 119, 0, 0,		// 88 : X
	0, 3, 4, 120, 4, 3, 0, 0,		// 89 : Y
	0, 0, 113, 73, 73, 71, 0, 0,	// 90 : Z
	0, 0, 127, 65, 65, 0, 0, 0,		// 91 : [
	0, 2, 4, 8, 16, 32, 64, 0,		// 92 : (\)
	0, 0, 0, 65, 65, 127, 0, 0,		// 93 : ]
	0, 4, 2, 1, 2, 4, 0, 0,			// 94 : ^
	0, 64, 64, 64, 64, 64, 64, 0,	// 95 : _
	0, 0, 1, 2, 4, 0, 0, 0,			// 96 : `
	0, 0, 48, 72, 40, 120, 0, 0,	// 97 : a
	0, 0, 127, 72, 72, 48, 0, 0,	// 98 : b
	0, 0, 48, 72, 72, 0, 0, 0,		// 99 : c
	0, 0, 48, 72, 72, 127, 0, 0,	// 100 : d
	0, 0, 48, 88, 88, 16, 0, 0,		// 101 : e
	0, 0, 126, 9, 1, 2, 0, 0,		// 102 : f
	0, 0, 80, 152, 152, 112, 0, 0,	// 103 : g
	0, 0, 127, 8, 8, 112, 0, 0,		// 104 : h
	0, 0, 0, 122, 0, 0, 0, 0,		// 105 : i
	0, 0, 64, 128, 128, 122, 0, 0,	// 106 : j
	0, 0, 127, 16, 40, 72, 0, 0,	// 107 : k
	0, 0, 0, 127, 0, 0, 0, 0,		// 108 : l
	0, 120, 8, 16, 8, 112, 0, 0,	// 109 : m
	0, 0, 120, 8, 8, 112, 0, 0,		// 110 : n
	0, 0, 48, 72, 72, 48, 0, 0,		// 111 : o
	0, 0, 248, 40, 40, 16, 0, 0,	// 112 : p
	0, 0, 16, 40, 40, 248, 0, 0,	// 113 : q
	0, 0, 112, 8, 8, 16, 0, 0,		// 114 : r
	0, 0, 72, 84, 84, 36, 0, 0,		// 115 : s
	0, 0, 8, 60, 72, 32, 0, 0,		// 116 : t
	0, 0, 56, 64, 32, 120, 0, 0,	// 117 : u
	0, 0, 56, 64, 56, 0, 0, 0,		// 118 : v
	0, 56, 64, 32, 64, 56, 0, 0,	// 119 : w
	0, 0, 72, 48, 48, 72, 0, 0,		// 120 : x
	0, 0, 24, 160, 160, 120, 0, 0,	// 121 : y
	0, 0, 100, 84, 84, 76, 0, 0,	// 122 : z
	0, 0, 8, 28, 34, 65, 0, 0,		// 123 : {
	0, 0, 0, 126, 0, 0, 0, 0,		// 124 : |
	0, 0, 65, 34, 28, 8, 0, 0,		// 125 : }
	0, 0, 4, 2, 4, 2, 0, 0,			// 126 : ~
	0, 120, 68, 66, 68, 120, 0, 0,	// 127 : (DEL)
};




