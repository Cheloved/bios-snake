#include "keyboard.h"

volatile uint8_t key_pressed = 0;
volatile uint8_t current_key = 0;

void update_dir(uint8_t scancode)
{
    switch ( scancode )
    {
        case 0x11: dir = 0; break; // W
        case 0x20: dir = 1; break; // D
        case 0x1F: dir = 2; break; // S
        case 0x1E: dir = 3; break; // A
    }
}

/*void __attribute__((interrupt)) kbd_handler(void)*/
void kbd_handler()
{
    // Чтение с порта клавиатуры
    uint8_t scancode;
    __asm__ __volatile__ ("inb $0x60, %0" : "=a"(scancode));

    // Игнорируем отпускание клавиши
    if ( scancode & 0x80 )
        return;

    /*key_pressed = 1;*/
    /*current_key = scancode;*/

    char msg[] = "Key: 00\r\n";
    msg[5] = "0123456789ABCDEF"[ scancode >> 4 ];
    msg[6] = "0123456789ABCDEF"[ scancode & 0x0F ];
    print_string(msg);
    /**/
    /*print_string("Key pressed\r\n");*/

    update_dir(scancode);
    /*return;*/
}
