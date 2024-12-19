#include "puts.h"

void init_vga() {
    vga = (char*)0xB8000;
}

void putc(char c) {
    if (c == '\n') {  // Handle newlines (optional)
        vga += 160;   // Move to the next line (80 columns * 2 bytes per column)
        return;
    }
    *vga = c;         // Write the character
    *(vga + 1) = 0x07; // Set attribute byte (light gray on black)
    vga += 2;         // Move to the next character cell
}

void puts(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) { // Correctly iterate over the string
        putc(str[i]);
    }
}