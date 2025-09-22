#ifndef __RGB_LED__
#define __RGB_LED__


void neopixel_begin(void);
void neopixel_show(void);
void neopixel_setPixelColor(uint8_t i, uint32_t c);
void neopixel_setBrightness(uint8_t b);

void neopixel_init(void);
void neopixel_show_state(void);

#endif // __RGB_LED__
