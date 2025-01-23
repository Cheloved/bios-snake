#pragma once
#include <stdint.h>
#include "snake.h"
#include "screen.h"

extern volatile uint8_t key_pressed;
extern volatile uint8_t current_key;

void update_dir(uint8_t scancode);
void kbd_handler();
