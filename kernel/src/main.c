#include "puts.h"
#include "proc.h"
#include "mem.h"

extern void main() {
    init_vga();
    puts("Hello, world!\n");
    puts("Welcome to VGA text mode.\n");
    init_mem();
    init_user();
    scheduler();
    return;
}

//todo:
// fix print scroll and green
// find first address after kernel and free unti llast address
// create user proc
