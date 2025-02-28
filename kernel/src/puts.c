#include "puts.h"

typedef char* va_list;

#define VA_ALIGN sizeof(int)

#define va_start(ap, last) (ap = (va_list)&last + sizeof(last))

#define va_arg(ap, type) (*(type*)((ap += VA_ALIGN) - VA_ALIGN))

#define va_end(ap) (ap = NULL)

#define FIRST_CHAR 0xB8000

#define PAST_LAST_CHAR 0xB8FA0

#define LAST_LINE_FIRST 0xB8F00

void init_vga() {
    vga = (char*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {  // 80 columns x 25 rows
        *(char*)(0xB8000 + i * 2) = ' ';     // Clear character
        *(char*)(0xB8000 + i * 2 + 1) = 0x07; // Default attribute (light gray on black)
    }
}

void putc(char c) {
    //scroll
    if ((int)vga >= PAST_LAST_CHAR) {
        for (int i = FIRST_CHAR; i < LAST_LINE_FIRST; i++) {
            *(char*)i = *(char*)(i+80*2);
        }
        for (int i = LAST_LINE_FIRST; i < PAST_LAST_CHAR; i+=2) {
            *(char*)i = ' ';
            *(char*)(i+1) = 0x07;
        }
        vga = (char*)(0xB8FA0 - 80 * 2);
    }

    if (c == '\n') {  // Handle newlines
        unsigned int offset = (vga - (char*)0xB8000) / 2;  // Current character position
        unsigned int next_line_offset = (offset / 80 + 1) * 80; // Move to next line
        vga = (char*)0xB8000 + next_line_offset * 2; // Calculate the address
        return;
    }
    *vga = c;         // Write the character
    *(vga + 1) = 0x07; // Set attribute byte (light gray on black)
    vga += 2;         // Move to the next character cell
}

void puthex(unsigned int num) {
    putc('0');
    putc('x');

    if (num == 0) {
        putc('0');
        return;
    }

    char buffer[8]; // Enough to hold 8 hex digits for a 32-bit integer
    int i = 0;

    // Extract hex digits into the buffer
    while (num != 0) {
        unsigned int digit = num % 16;
        if (digit < 10) {
            buffer[i++] = digit + '0'; // Convert 0-9 to characters
        } else {
            buffer[i++] = digit - 10 + 'A'; // Convert 10-15 to 'A'-'F'
        }
        num /= 16;
    }

    // Print digits in reverse order (from most significant to least significant)
    while (i > 0) {
        putc(buffer[--i]);
    }
}

void putint(int num) {
    if (num == 0) { 
        putc('0');
        return;
    }
    if (num < 0) { 
        putc('-');
        num = -num;
    }
    char buffer[10];
    int i = 0;

    while (num != 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0) {
        putc(buffer[--i]);
    }
}

void puts(const char* str, ...) {
    va_list args;
    va_start(args, str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '%' && str[i+1] == 'd') {
            int value = va_arg(args, int);
            putint(value);
            i++;
        } else if (str[i] == '%' && str[i+1] == 'x') {
            unsigned int value = va_arg(args, unsigned int);
            puthex(value);
            i++;
        } else {
            putc(str[i]);
        }  
    }
}

int strcmp(char* s1, char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}