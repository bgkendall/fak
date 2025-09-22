#include "caps_word.h"

#include "ch55x.h"

#include "time.h"
#include "split_central.h"
#include "rgbled.h"

__bit caps_word_state = 0;

void set_caps_word_state(__bit new_state)
{
    if (new_state != caps_word_state)
    {
        caps_word_state = new_state;

#ifdef NEOPIXEL_ENABLE
        neopixel_show_state();
#endif
    }
}

void caps_word_on() {
    set_caps_word_state(1);
}

void caps_word_off() {
    set_caps_word_state(0);
}

void caps_word_toggle() {
    set_caps_word_state(!caps_word_state);
}

__bit caps_word_active() {
    return caps_word_state;
}

__bit caps_word_handle_key(uint8_t code, uint8_t shift_pressed) {
  if (caps_word_state == 0) {
    return 0;
  }

  // check hasn't timed out
  if ((get_timer() - get_last_tap_timestamp()) > 5000) {
    caps_word_off();
    return 0;
  }

  // this assumes US layout on the host OS.
  if ((code >= 0x04) && code < (0x04 + 26)) {
    // A..Z
    return 1;
  } else if (!shift_pressed && (code >= 0x04 + 26) && code < (0x04 + 26 + 10)) { // 1..0
  } else if (code == 0x2A) { // backspace
  } else if (code == 0x2D) { // minus
    return 1;
  } else if (code == 0x4C) { // delete
  } else {
    // otherwise: not an accepted key; disable caps word
    caps_word_off();
  }

  return 0;
}
