#pragma once
#include <stdint.h>
#include "time.h"

// Генерирует случайное число засчет
// чтения младших битов счетчика системного времени
uint16_t rand();
