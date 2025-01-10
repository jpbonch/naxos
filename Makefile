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
		build/proc.o build/mem.o build/init_elf.o build/fs.o build/exec.o build/syscall.o build/idt.o
	objcopy -O binary build/kernel.elf build/kernel.bin

build/os.bin: build/kernel.bin
	# Create epicos.bin with bootloader and kernel
	cat build/boot.o build/kernel.bin > build/epicos.bin
	dd if=/dev/zero bs=512 count=16 >> build/epicos.bin  # Ensure at least 16 sectors
	truncate -s $$((17 * 512)) build/epicos.bin            # Ensure exactly 17 sectors

	# Prepare filesystem header
	python3 user/makefs.py

	cat build/epicos.bin build/filesystem_header.bin > build/os.bin


run: build/os.bin
	@echo "$(VAR1)" > build/run.sh
	chmod +x build/run.sh
	@echo "$(VAR2)" > build/debug.sh
	chmod +x build/debug.sh

clean:
	rm -f build/*
