#include "rgbled.h"


#define NUM_BYTES (NUM_LEDS*COLOR_PER_LEDS)
#if NUM_BYTES > 255
#   error "NUM_BYTES can not be larger than 255."
#endif
__xdata uint8_t ledData[NUM_BYTES];

/***********************************************************************/
uint8_t neopixel_brightness = 255;

#define CONCAT(X, Y) CONCAT_(X, Y)
#define CONCAT_(X, Y) X##Y

#define NEOPIXEL_SHOW_FUNC CONCAT(neopixel_show_, NEOPIXEL_PIN)



SBIT(NEOPIXEL_PIN, NEOPIXEL_PIN_PORT, NEOPIXEL_PIN_BIT);


void neopixel_begin(void)
{
    __data uint8_t bit = 1 << NEOPIXEL_PIN_BIT;

    if (NEOPIXEL_PIN_PORT == P1_ADDR)
    {
        P1_MOD_OC &= ~bit;
        P1_DIR_PU |= bit;
    }
    // else if (NEOPIXEL_PIN_PORT == P3_ADDR)
    // {
    //     P3_MOD_OC &= ~bit;
    //     P3_DIR_PU |= bit;
    // }
}

void neopixel_show(void)
{
    NEOPIXEL_SHOW_FUNC(ledData, NUM_BYTES); //Possible to use other pins.
}

void neopixel_setPixelColor(uint8_t i, uint32_t c)
{
    uint16_t r, g, b;
    r = (((c >> 16) & 0xFF) * neopixel_brightness) >> 8;
    g = (((c >> 8) & 0xFF) * neopixel_brightness) >> 8;
    b = ((c & 0xFF) * neopixel_brightness) >> 8;

    set_pixel_for_GRB_LED(ledData, i, r, g, b);
}

void neopixel_setBrightness(uint8_t b)
{
    neopixel_brightness = b;
}
