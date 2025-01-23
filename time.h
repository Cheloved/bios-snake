#pragma once
#include <stdint.h>

extern volatile uint16_t timer_ticks;

uint16_t get_ticks();
void wait(uint16_t ms);

