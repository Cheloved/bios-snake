#include "random.h"

uint16_t rand()
{
    return timer_ticks * 214013 + 2531011;
}
