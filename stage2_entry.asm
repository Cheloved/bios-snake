[bits 16]

global _start
extern main, kbd_handler

_start:
    jmp 0x0000:start

start:
    ; Установка обработчика клавиатуры
    ; Замена вектора 0x09
    cli
    xor ax, ax
    mov es, ax
    mov word [es:0x09*4], keyboard_isr ; Смещение обработчика
    mov word [es:0x09*4+2], 0x0000     ; Сегмент обработчика
    sti

    ; Переход к основному циклу в С
    call main
    jmp $

keyboard_isr:
    pusha
    push es

    ;call kbd_handler ; Вызов обработчика
    in al, 0x60
    mov al, '+'
    mov ah, 0x0e
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
    
    mov al, 0x20     ; Отправка EOI(End Of Interrupt)
    out 0x20, al

    pop es
    popa
    iret
