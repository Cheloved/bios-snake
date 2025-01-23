# Конфигурация
CC := gcc
ASM := nasm
LD = ld
QEMU := qemu-system-x86_64

# Флаги
ASMFLAGS := -f bin
CFLAGS := -O0 -nostdlib -ffreestanding -fno-pie -fno-pic \
		  -mno-red-zone -m16 -march=i386 -mtune=i386
LDFLAGS := -m elf_i386 -T linker.ld -nostdlib --oformat binary

# Исходные файлы
BOOT_SRC := boot.asm
STAGE2_ENTRY := stage2_entry.asm
STAGE2_SRCS := stage2.c $(wildcard *.c)
STAGE2_OBJS := stage2_entry.o $(STAGE2_SRCS:.c=.o)

# Цели по умолчанию
all: disk.img

# Сборка загрузчика
boot.bin: $(BOOT_SRC)
	$(ASM) $(ASMFLAGS) $< -o $@

# Cборка stage2_entry
stage2_entry.o: $(STAGE2_ENTRY)
	$(ASM) -f elf32 $< -o $@

# Компиляция С-файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Линковка stage2
stage2.bin: $(STAGE2_OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

# Создание образа диска
disk.img: boot.bin stage2.bin
	cat $^ > $@
	dd if=/dev/zero bs=512 count=1000 >> $@

# Запуск в QEMU
run: disk.img
	# $(QEMU) -nographic -drive format=raw,file=$<
	$(QEMU) -display curses -serial stdio -drive format=raw,file=$<

# Очистка
clean:
	rm -f *.o *.bin *.img

.PHONY: all run clean
