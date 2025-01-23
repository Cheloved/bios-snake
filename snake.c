#include "snake.h"

uint16_t length = 0;
Node tail[80*25] = {0};
volatile uint8_t dir = 2;

void init_snake()
{
    for ( uint16_t i = 0; i < 20*20; i++ )
        tail[i] = (Node){ -1, -1 };
}

void erase_snake()
{
    volatile char* vmem = (volatile char*)0xB8000;

    for ( uint16_t i = 0; i < 80*25; i++ )
    {
        if ( tail[i].x == -1 )
            break;

        // Очистить клетку
        vmem[(tail[i].y*80+tail[i].x)*2] = ' ';
        vmem[(tail[i].y*80+tail[i].x)*2+1] = 0x07;
    }
}

void draw_snake()
{

    volatile char* vmem = (volatile char*)0xB8000;

    for ( uint16_t i = 0; i < 80*25; i++ )
    {
        if ( tail[i].x == -1 )
            break;

        char c = 'o';
        if ( i == 0 )
            c = 'O';

        vmem[(tail[i].y*80+tail[i].x)*2] = c;
        vmem[(tail[i].y*80+tail[i].x)*2+1] = 0x07;
    }
}

void move_snake()
{
    // Предварительное изменение координат
    Node buffer = { .x=tail[0].x, .y=tail[0].y };
    switch ( dir )
    {
        case 0:
            buffer.y--;
            break;
        case 1:
            buffer.x++;
            break;
        case 2:
            buffer.y++;
            break;
        case 3:
            buffer.x--;
            break;
    }

    // Проверка движения в обратную сторону
    if ( buffer.x == tail[1].x && buffer.y == tail[1].y )
        return;

    // Перемещение по цепочке с конца
    for ( uint16_t i = length-1; i >= 1; i-- ) 
    {
        tail[i].x = tail[i-1].x;
        tail[i].y = tail[i-1].y;
    }
    tail[0].x = buffer.x;
    tail[0].y = buffer.y;
}
