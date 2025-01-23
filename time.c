#include "time.h"

__attribute__((section(".data"))) volatile uint16_t timer_ticks = 0;

uint16_t get_ticks() { return timer_ticks; }

void wait(uint16_t ms)
{
    uint16_t target = timer_ticks + (ms / 55);
    while ( timer_ticks < target ) __asm__("hlt");
}
