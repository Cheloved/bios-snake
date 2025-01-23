#pragma once
#include <stdint.h>
#include "random.h"

extern uint8_t game_over;

// Для хранения координат каждой секции
typedef struct Node
{
    uint16_t x;
    uint16_t y;
} Node;

// Хранит всю змею
extern uint16_t length;
extern Node tail[80*25];
extern Node food;

// Определяет направление движения*/
// 0 - вверх
// 1 - вправо
// 2 - вниз
// 3 - влево
extern volatile uint8_t dir __attribute__((aligned(2)));

void init_food();
void draw_food();

// Инициализация всех сегментов
// координатами -1, -1
void init_snake();

// Добавляет символы змеи на поле
void draw_snake();

// Стираетсимволы змеи на поле
void erase_snake();

// Просчет коллизий
void check_collisions();

// Пересчитывает координаты
void move_snake();
