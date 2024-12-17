all: run
VAR1 = qemu-system-i386 -drive format=raw,file=build/boot.img,index=0,media=disk -nographic


# Assemble the bootloader into a binary format
build/boot.o: boot.asm
	nasm -f elf32 boot.asm -o build/boot.o

build/main.o: main.c
	gcc -ffreestanding -m32 -c main.c -o build/main.o

build/kernel.bin: build/boot.o build/main.o
	ld -m elf_i386 -N -Ttext 0x7C00 -o build/kernel.elf build/boot.o build/main.o
	objcopy -O binary build/kernel.elf build/kernel.bin

# Create the bootable image using dd
build/boot.img: build/kernel.bin
	dd if=build/kernel.bin of=build/boot.img bs=512 count=1

# Run the boot image in QEMU
run: build/boot.img
	@echo $(VAR1) > build/run.sh
	chmod +x build/run.sh
	
# Clean up the generated files
clean:
	rm -f build/*

