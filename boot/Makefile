
all: ../build/boot.o ../build/kernel_entry.o

../build/boot.o: boot.asm
	nasm -f bin boot.asm -o ../build/boot.o

../build/kernel_entry.o: kernel_entry.asm
	nasm -f elf32 kernel_entry.asm -o ../build/kernel_entry.o