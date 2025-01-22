org 0x7c00
bits 16

start:
    ; Настройка сегментных регистров
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; Настройка стека
    mov ss, ax
    mov sp, 0x7c00

    ; Начальный текст
    mov si, msg
    call print_string

	; Чтение второго этапа с диска
    mov ah, 0x02        ; Функция чтения секторов
    mov al, 0x04        ; Количество секторов для чтения
    mov ch, 0           ; Цилиндр
    mov dh, 0           ; Головка
    mov cl, 2           ; Сектор (MBR - 1, второй этап с 2)
    mov bx, 0x7e00      ; Адрес, куда грузить второй этап
    int 0x13

    jc disk_error       ; Проверка ошибки (CF=1 при ошибке)
    ; При отсутствии ошибки, вывести соотв. сообщение
    mov si, msg2
    call print_string

    jmp 0x7e00          ; Переход ко второму этапу

disk_error:
    mov si, error_msg
    call print_string
    hlt

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

; Данные
msg db "MBR Bootloader loaded", 0xD, 0xA, 0
msg2 db "Proceeding to stage 2", 0xD, 0xA, 0
error_msg db "Disk error!", 0

; Заполнение до 512 байт
times 510 - ($ - $$) db 0
dw 0xaa55
