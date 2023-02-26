#include <stdint.h>


uint8_t spi_send_recv(uint8_t data);

void display_init(void);

void display_debug( volatile int * const addr );

void display_update(void);

void display_string(int line, char *s);
void display_image(int x, const uint8_t *data);

/* ----- NEW STUFF ----- */
void display_black(void);