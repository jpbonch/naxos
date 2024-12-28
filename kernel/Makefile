# List of source files
SRC_FILES := src/main.c src/puts.c src/proc.c

# Automatically generate a list of object files in ../build/
OBJ_FILES := $(patsubst src/%.c,../build/%.o,$(SRC_FILES))

# Default target
all: $(OBJ_FILES)

# Pattern rule for compiling .c files into .o files
../build/%.o: src/%.c
	gcc -g -ffreestanding -m32 -c $< -o $@ -fno-pie -Iinclude

# Clean up build artifacts
clean:
	rm -f $(OBJ_FILES)