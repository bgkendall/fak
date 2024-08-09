#ifndef CAPS_WORD_H_
#define CAPS_WORD_H_

#include <stdint.h>

#include "ch55x.h"

void caps_word_on(void);
void caps_word_off(void);
void caps_word_toggle(void);

__bit caps_word_active(void);

// Process the logic for caps word for the given key.
//
// If keys other than A-Z, 0-9, -, _, backspace, delete are pressed,
// exit caps word mode.
//
// Does nothing if caps word word is not active.
//
// Returns 1 if the needs to press shift key for the key, 0 otherwise.
__bit caps_word_handle_key(uint8_t code, uint8_t shift_pressed);

#endif // CAPS_WORD_H_
