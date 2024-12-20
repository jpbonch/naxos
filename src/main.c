#include "puts.h"

extern void main() {
    init_vga();
    puts("Hello, world!\n");
    puts("Welcome to VGA text mode.");
    return;
}
