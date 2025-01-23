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
    /*__asm__ __volatile__*/
    /*    (*/
    /*        "int $0x10"*/
    /*        :*/
    /*        : "a" (0x0003)*/
    /*    );*/

    __asm__ __volatile__("cli");
    volatile char* vmem = (volatile char*)0xB8000;
    for ( int i = 0; i < 80*25*2; i += 2 )
    {
        vmem[i] = ' ';
        vmem[i+1] = 0x07;
    }
    __asm__ __volatile__("sti");
}

void draw_map()
{
    volatile char* vmem = (volatile char*)0xB8000;

    // Заполняет всё поле пробелами
    for ( uint16_t i = 0; i < 80*24*2; i+=2 )
    {
        vmem[i] = ' ';
        vmem[i+1] = 0x07;
    }

    // Верхняя и нижняя границы
    for ( uint16_t i = 0; i < 80*2; i+=2 )
    {
        vmem[i] = '_';
        vmem[i+1] = 0x07;

        vmem[i + 80*2*24] = '_';
        vmem[i + 80*2*24 + 1] = 0x07;
    }
    
    // Боковые границы
    for ( uint16_t i = 0; i < 24*2; i+=2 )
    {
        vmem[80*i] = '|';
        vmem[80*i+1] = 0x07;

        vmem[80*i+79*2] = '|';
        vmem[80*i+79*2+1] = 0x07;
    }
}
