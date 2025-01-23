#include <stdint.h>

#include "snake.h"
#include "map.h"
#include "screen.h"
#include "time.h"
#include "keyboard.h"

void main()
{
    print_string("Stage 2 (C) loaded\r\n");
    clear_screen();
    reset_map();
    /*print_string(map);*/
    init_snake();

    symbol = 0x99;
    char test[13] = "Symbol: ++\r\n";

    dir = 2;
    length = 3;
    tail[0] = (Node){ 10, 10 };
    tail[1] = (Node){ 10, 9 };
    tail[2] = (Node){ 10, 8 };

    uint16_t last_update = 0;
    while ( 1 )
    {
        // Таймер на основе системных тиков
        uint16_t current_time = get_ticks();

        if ( current_time - last_update >= 10 )
        {
            clear_screen();

            draw_snake(); 
            print_string(map);
            update_dir(symbol);
            move_snake();

            test[8] = "0123456789ABCDEF"[ symbol >> 4 ];
            test[9] = "0123456789ABCDEF"[ symbol & 0x0F ];
            print_string(test);

            last_update = current_time;
        }

        // Обработка флагов прерываний
        __asm__ __volatile__ ("hlt");
    }

    while(1);

    return;
}
