[bits 16]

global _start
extern main
extern timer_ticks
extern symbol

section .text
_start:
    jmp 0x0000:start

start:
    ; Настройка сегментных регистров
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; Настройка стека
    mov ss, ax
    mov sp, 0x7c00

    ; Установка обработчика клавиатуры
    ; Замена вектора 0x09
    cli
    xor ax, ax
    mov es, ax
    mov word [es:0x09*4], keyboard_isr ; Смещение обработчика
    mov word [es:0x09*4+2], ax         ; Сегмент обработчика
    sti

    ; Установка обработчика таймера
    cli
    mov word [es:0x08*4], timer_isr
    mov word [es:0x08*4+2], ax
    sti

    ; Переход к основному циклу в С
    call main

    jmp $

keyboard_isr:
    pusha
    push ds
    push es

    xor ax, ax
    mov ds, ax
    mov es, ax

    in al, 0x60      ; Получить код
    xor ah, ah
    mov [symbol], al ; Записать его в глобальную переменную

    mov al, 0x20     ; Отправка EOI(End Of Interrupt)
    out 0x20, al

    pop es
    pop ds
    popa
    iret

timer_isr:
    pusha
    push ds

    xor ax, ax
    mov ds, ax
    inc word [timer_ticks]

    mov al, 0x20
    out 0x20, al

    pop ds
    popa
    iret

