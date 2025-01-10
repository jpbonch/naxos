all: elf/init_elf.o


build/init.o:
	gcc -g -ffreestanding -m32 -c src/init.c -o build/init.o -fno-pie -Iinclude

build/init.elf: build/init.o
	ld -m elf_i386 -Ttext 0x0 -o build/init.elf build/init.o

elf/init_elf.o: build/init.elf
	ld -m elf_i386 -r -b binary -o elf/init_elf.o build/init.elf