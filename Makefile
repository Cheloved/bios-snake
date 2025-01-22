all:
	nasm -f bin boot.asm -o boot.bin
	gcc -O0 -nostdlib -ffreestanding -fno-pie -fno-pic \
		-mno-red-zone \
		-m16 -march=i386 -mtune=i386 -c stage2.c -o stage2.o
	ld -m elf_i386 -T linker.ld --oformat binary -nostdlib stage2_entry.o stage2.o -o stage2.bin
run:
	nasm -f bin boot.asm -o boot.bin
	nasm -f elf32 stage2_entry.asm -o stage2_entry.o
	gcc -O0 -nostdlib -ffreestanding -fno-pie -fno-pic \
		-mno-red-zone \
		-m16 -march=i386 -mtune=i386 -c stage2.c -o stage2.o
	ld -m elf_i386 -T linker.ld --oformat binary -nostdlib stage2_entry.o stage2.o -o stage2.bin
	cat boot.bin stage2.bin > disk.img
	dd if=/dev/zero bs=512 count=1000 >> disk.img
	qemu-system-x86_64 -nographic -drive format=raw,file=disk.img
