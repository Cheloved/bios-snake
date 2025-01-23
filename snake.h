#pragma once
#include <stdint.h>
#include "map.h"

// Для хранения координат каждой секции
typedef struct Node
{
    uint16_t x;
    uint16_t y;
} Node;

// Хранит всю змею
extern Node tail[20*20];

extern char dir; // Определяет направление движения
                 // 0 - вверх
                 // 1 - вправо
                 // 2 - вниз
                 // 3 - влево

// Инициализация всех сегментов
// координатами -1, -1
void init_snake();

// Добавляет символы змеи на поле
void draw_snake();

