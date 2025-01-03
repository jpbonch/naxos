# List of source files
SRC_FILES := src/main.c src/puts.c src/proc.c src/init.c src/mem.c

# Automatically generate a list of object files in ../build/
OBJ_FILES := $(patsubst src/%.c,../build/%.o,$(SRC_FILES))

# Default target
all: $(OBJ_FILES) ../build/init_elf.o

# Pattern rule for compiling .c files into .o files
../build/%.o: src/%.c
	gcc -g -ffreestanding -m32 -c $< -o $@ -fno-pie -Iinclude

# Link init.o into init.elf
../build/init.elf: $(wildcard ../build/*.o)
	ld -m elf_i386 -Ttext 0x0 -o ../build/init.elf ../build/init.o

# Convert init.elf into an object that embeds the raw bytes
../build/init_elf.o: ../build/init.elf
	ld -m elf_i386 -r -b binary -o ../build/init_elf.o ../build/init.elf


# Clean up build artifacts
clean:
	rm -f $(OBJ_FILES)