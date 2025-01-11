all: run

VAR1 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -serial mon:stdio -curses
VAR2 = qemu-system-i386 -drive format=raw,file=build/os.bin,index=0,media=disk -nographic -s -S -serial mon:stdio -curses

kernel_make:
	make -C kernel

boot_make:
	make -C boot

build/kernel.bin: kernel_make boot_make
	ld -m elf_i386 -T linker.ld -o build/kernel.elf \
		build/kernel_entry.o build/main.o build/puts.o \
		build/proc.o build/mem.o build/uinit build/fs.o build/exec.o build/syscall.o build/idt.o
	objcopy -O binary build/kernel.elf build/kernel.bin

build/os.bin: build/kernel.bin
	# Create epicos.bin with bootloader and kernel
	cat build/boot.o build/kernel.bin > build/epicos.bin
	dd if=/dev/zero bs=512 count=36 >> build/epicos.bin 
	truncate -s $$((37 * 512)) build/epicos.bin         

	make -C user
	# Prepare filesystem header
	python3 user/makefs.py

	cat build/epicos.bin build/filesystem.bin > build/os.bin


run: build/os.bin
	@echo "$(VAR1)" > build/run.sh
	chmod +x build/run.sh
	@echo "$(VAR2)" > build/debug.sh
	chmod +x build/debug.sh

clean:
	rm -f build/*
	rm -f user/build/*
	rm -f user/elf/*
