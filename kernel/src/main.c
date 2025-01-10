#include "puts.h"
#include "proc.h"
#include "mem.h"
#include "fs.h"
#include "idt.h"

extern void main() {
    init_vga();
    puts("Hello, world!\n");
    puts("Welcome to VGA text mode.\n");
    load_idt();
    init_mem();
    init_fs();
    init_user();
    scheduler();
    return;
}

//todo:
// kernel stack for each process
// implement syscalls