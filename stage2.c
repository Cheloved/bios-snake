#include <stdint.h>

#include "snake.h"
#include "map.h"
#include "screen.h"
#include "time.h"

void main()
{
    print_string("Stage 2 (C) loaded\r\n");
    clear_screen();
    reset_map();
    print_string(map);
    init_snake();

    tail[0] = (Node){ 10, 10 };
    tail[1] = (Node){ 10, 9 };
    tail[2] = (Node){ 10, 8 };

    while ( 1 )
    {
        clear_screen();
        draw_snake(); 
        print_string(map);
        wait(100);
    }

    while(1);
}
