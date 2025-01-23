#include "time.h"

void wait_1ms()
{
    __asm__ __volatile__
        (
            "int $0x15"
            :
            : "a" (0x8600), "c" (0x0000), "d" (0x03e8)
        );
}

void wait(uint16_t ms)
{
    while ( ms-- )
        wait_1ms();
}
