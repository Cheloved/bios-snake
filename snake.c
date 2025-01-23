#include "snake.h"

uint8_t game_over = 0;
uint16_t length = 0;
Node tail[80*25] = {0};
Node food = {0};
volatile uint8_t dir = 2;

void init_snake()
{
    for ( uint16_t i = 0; i < 80*25; i++ )
        tail[i] = (Node){ -1, -1 };
}

void init_food()
{
    food.x = 1 + rand() % 78;
    food.y = 1 + rand() % 22;
}

void draw_food()
{
    volatile char* vmem = (volatile char*)0xB8000;

    vmem[(food.y*80+food.x)*2] = 'x';
    vmem[(food.y*80+food.x)*2+1] = 0x0A;
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

void check_collisions()
{
    for ( uint16_t i = 1; i < 80*25; i++ )
    {
        if ( tail[i].x == -1 )
            break;

        if ( tail[0].x == tail[i].x &&
             tail[0].y == tail[i].y)
        {
            game_over = 1;
            return;
        }
    }
    if ( tail[0].x == 0 || tail[0].x == 79 ||
         tail[0].y == 0 || tail[0].y == 24)
    {
        game_over = 1;
        return;
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

    uint16_t i = length - 1;
    // Если получена еда
    if ( tail[0].x == food.x && tail[0].y == food.y )
    {
        if ( length < 80*25 - 1 )
        {
            tail[length] = tail[length-1];
            length++;
        }
        init_food();
    }

    // Перемещение по цепочке с конца
    for ( i; i >= 1; i-- ) 
        tail[i] = tail[i-1];
    tail[0] = buffer;
}
