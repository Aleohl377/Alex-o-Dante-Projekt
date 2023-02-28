#include <stdint.h>


uint8_t spi_send_recv(uint8_t data);

void display_init(void);

void display_debug( volatile int * const addr );

void display_update(void);

void display_string(int line, char *s);
void display_image(int x, const uint8_t *data);

/* ----- NEW STUFF ----- */
void update_display_bitmap(int width, int height, int x, int y, const uint8_t *data);
void push_bitmap_to_display_buffer(void);
void update_display_buffer(const uint8_t *data);
void clear_display_bitmap(void);
void draw_display(void);

void display_white(void);
void display_black(void);
void ground_init(void);

int simple_pow(int x, int y);

void Game_init(void);
void Game_loop(void);