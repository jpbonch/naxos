#include "puts.h"
#include "proc.h"

extern void main() {
    init_vga();
    puts("Hello, world!\n");
    puts("Welcome to VGA text mode.\n");
    init_mem();
    alloc_page();
    return;
}

//todo:
// fix print scroll and green
// find first address after kernel and free unti llast address
// create user proc
