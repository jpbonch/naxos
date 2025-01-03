all: run

VAR1 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -serial mon:stdio -curses
VAR2 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -s -S -serial mon:stdio -curses

kernel_make:
	make -C kernel

boot_make:
	make -C boot

build/kernel.bin: kernel_make boot_make
	ld -m elf_i386 -T linker.ld -o build/kernel.elf build/kernel_entry.o build/main.o build/puts.o build/proc.o build/mem.o build/init_elf.o
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
