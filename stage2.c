void print_string(const char* str)
{
    while(*str)
    {
        /*
         * mov ah, 0e
         * mov al, [si]
         * inc si
         * mov bh, 0
         * mov bl, 7
        */ 
        __asm__ __volatile__
            (
                "int $0x10"
                :
                : "a" (0x0e00 | *str++), "b" (0x000f)
            );
    }
}

void clear_screen()
{
    __asm__ __volatile__
        (
            "int $0x10"
            :
            : "a" (0x0600), "b" (0x07), "c" (0), "d" (0x184f)
        );
}

void main()
{
    /*clear_screen();*/
    print_string("Stage 2 (C) loaded\r\n");
    while(1);
}
