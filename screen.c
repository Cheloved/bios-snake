#include "screen.h"

void print_string(const char* str)
{
    while(*str)
    {
        /*
         * mov ah, 0e
         * mov al, [si]
         * inc si
         * mov bh, 0
         * mov bl, 7
        */ 
        __asm__ __volatile__
            (
                "int $0x10"
                :
                : "a" (0x0e00 | *str++), "b" (0x000f)
            );
    }
}

void clear_screen()
{
    // Установка видео режима 80x25
    // очищает экран
    __asm__ __volatile__
        (
            "int $0x10"
            :
            : "a" (0x0003)
        );
}
