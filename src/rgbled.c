#include "rgbled.h"
#include "caps_word.h"
#include "keymap.h"
#include "WS2812.h"


#if NEOPIXEL_BUFFER_LEN > 255
#   error "NEOPIXEL_BUFFER_LEN can not be larger than 255."
#endif
__xdata __at(XADDR_NEOPIXEL_BUFFER) uint8_t ledData[NEOPIXEL_BUFFER_LEN];
__xdata __at(XADDR_NEOPIXEL_BRIGHTNESS) uint8_t neopixel_brightness = 255;


/***********************************************************************/

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
    NEOPIXEL_SHOW_FUNC(ledData, NEOPIXEL_BUFFER_LEN); //Possible to use other pins.
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

void neopixel_init(void)
{
    neopixel_begin();
    neopixel_setBrightness(128);
    neopixel_setPixelColor(0, 0xFFFFFF);
    neopixel_show();
}

void neopixel_show_state(void)
{
    if (caps_word_active())
    {
        neopixel_setPixelColor(0, 0xFF1E1E);
    }
    else
    {
        switch (get_highest_layer_idx())
        {
            case 4:
            case 5:
            {
                neopixel_setPixelColor(0, 0xFF4400);
                break;
            }
            case 6:
            case 7:
            {
                neopixel_setPixelColor(0, 0x00FF00);
                break;
            }
            case 8:
            {
                neopixel_setPixelColor(0, 0xFF00FF);
                break;
            }
            default:
            {
                neopixel_setPixelColor(0, 0x000000);
                break;
            }
        }
    }

    neopixel_show();
}
