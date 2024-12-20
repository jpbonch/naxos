all: run
VAR1 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -serial mon:stdio -curses
VAR2 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -s -S -serial mon:stdio -curses

# Assemble the bootloader into a binary format
build/boot.o: boot.asm
	nasm -f bin boot.asm -o build/boot.o

build/kernel_entry.o: kernel_entry.asm
	nasm -f elf32 kernel_entry.asm -o build/kernel_entry.o

build/main.o: src/main.c
	gcc -g -ffreestanding -m32 -c src/main.c -o build/main.o -fno-pie -Iinclude

build/puts.o: src/puts.c
	gcc -g -ffreestanding -m32 -c src/puts.c -o build/puts.o -fno-pie -Iinclude

build/kernel.bin: build/boot.o build/main.o build/puts.o build/kernel_entry.o
	ld -m elf_i386 -T linker.ld -o build/kernel.elf build/kernel_entry.o build/main.o build/puts.o
	objcopy -O binary build/kernel.elf build/kernel.bin
	cat build/boot.o build/kernel.bin > build/os.bin

# Run the boot image in QEMU
run: build/kernel.bin
	@echo $(VAR1) > build/run.sh
	chmod +x build/run.sh
	@echo $(VAR2) > build/debug.sh
	chmod +x build/debug.sh
	
# Clean up the generated files
clean:
	rm -f build/*
