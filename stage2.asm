org 0x7e00
bits 16

stage2:
    mov si, stage2_msg
    call print_string

    jmp $

print_string:
    pusha
.loop:
    lodsb       ; Загрузка символа из SI в AL
    or al, al   ; Проверка на конец строки
    jz .done

    mov ah, 0x0e    ; Функция вывода символа
    mov bh, 0       ; Номер страницы
    int 0x10

    jmp .loop
.done:
    popa
    ret

stage2_msg db "Stage 2 loaded", 0xd, 0xa, 0
