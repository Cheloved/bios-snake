#include <stdint.h>

#include "snake.h"
#include "screen.h"
#include "time.h"
#include "keyboard.h"

void main()
{
    print_string("Stage 2 (C) loaded\r\n");
    clear_screen();
    init_snake();
    draw_map();
    init_food();

    dir = 2;
    length = 3;
    tail[0] = (Node){ 10, 10 };
    tail[1] = (Node){ 10, 9 };
    tail[2] = (Node){ 10, 8 };

    uint16_t last_update = 0;
    while ( !game_over )
    {
        // Таймер на основе системных тиков
        uint16_t current_time = get_ticks();
        update_dir(symbol);

        if ( current_time - last_update >= 2 )
        {
            // Перерисовать змейку
            erase_snake();
            move_snake();
            check_collisions();
            draw_snake(); 
            draw_food();

            last_update = current_time;
        }

        // Обработка флагов прерываний
        __asm__ __volatile__ ("hlt");
    }

    print_string("Game over");
    while(1);

    return;
}
