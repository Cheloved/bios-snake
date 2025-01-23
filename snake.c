#include "snake.h"

Node tail[20*20] = {0};
char dir = 2;

void init_snake()
{
    for ( uint16_t i = 0; i < 20*20; i++ )
        tail[i] = (Node){ -1, -1 };
}

void draw_snake()
{
    reset_map();
    for ( uint16_t i = 0; i < 20*20; i++ )
    {
        if ( tail[0].x == -1 )
            break;

        char c = 'o';
        if ( i == 0 )
            c = 'O';

        map[ tail[i].y*22 + tail[i].x ] = c;
    }
}
