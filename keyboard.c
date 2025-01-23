#include "keyboard.h"

uint8_t symbol = 0x00;

void update_dir(uint8_t scancode)
{
    symbol = symbol & (uint8_t)(~0x80);
    __asm__ __volatile__ ("cli");
    switch ( scancode )
    {
        case 0x11: if(dir != 2) dir = 0; break; // W
        case 0x20: if(dir != 3) dir = 1; break; // D
        case 0x1F: if(dir != 0) dir = 2; break; // S
        case 0x1E: if(dir != 1) dir = 3; break; // A
    }
    __asm__ __volatile__ ("sti");
}

