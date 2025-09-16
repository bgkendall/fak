#ifndef __RGB_LED__
#define __RGB_LED__

#include "WS2812.h"

//#define NEOPIXEL_PIN P1_2
// #define NEOPIXEL_PIN_PORT P1_ADDR
// #define NEOPIXEL_PIN_BIT  2
// #define NUM_LEDS 1
#define COLOR_PER_LEDS 3


void neopixel_begin(void);
void neopixel_show(void);
void neopixel_setPixelColor(uint8_t i, uint32_t c);
void neopixel_setBrightness(uint8_t b);

#endif // __RGB_LED__
