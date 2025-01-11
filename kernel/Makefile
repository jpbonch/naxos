# List of source files
SRC_FILES := src/main.c src/puts.c src/proc.c src/uinit.c src/mem.c src/fs.c src/exec.c src/syscall.c src/idt.c

# Automatically generate a list of object files in ../build/
OBJ_FILES := $(patsubst src/%.c,../build/%.o,$(SRC_FILES))

# Default target
all: $(OBJ_FILES) ../build/uinit

# Pattern rule for compiling .c files into .o files
../build/%.o: src/%.c
	gcc -g -ffreestanding -m32 -c $< -o $@ -fno-pie -Iinclude

# Link init.o into init.elf
../build/uinit.elf: $(wildcard ../build/*.o)
	ld -m elf_i386 -Ttext 0x5600 -o ../build/uinit.elf ../build/uinit.o

# Convert init.elf into an object that embeds the raw bytes
../build/uinit: ../build/uinit.elf
	ld -m elf_i386 -r -b binary -o ../build/uinit ../build/uinit.elf


# Clean up build artifacts
clean:
	rm -f $(OBJ_FILES)