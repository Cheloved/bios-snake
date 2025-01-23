#pragma once
#include <stdint.h>
#include "snake.h"

// Содержит поле 20х20 символов
// + \r\n в конце каждой строки
extern char map[22*20];

// Очищает поле
void reset_map();

