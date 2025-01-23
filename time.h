#pragma once
#include <stdint.h>

// Ждет 1мс, используя системные прерывания
void wait_1ms();

// Ждет n мс, используя wait_1ms()
void wait(uint16_t ms);
