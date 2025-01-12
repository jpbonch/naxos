#include "puts.h"
#include "proc.h"
#include "mem.h"
#include "fs.h"
#include "idt.h"

extern void main() {
    init_vga();
    init_fs();
    puts("Hello, world!\n");
    puts("Welcome to VGA text mode.\n");
    load_idt();
    init_mem();
    init_user();
    scheduler();
    return;
}

//todo:
// kernel stack for each process
// implement syscalls, fork first
// properly handle ring 0 - ring 3
// make entry point outside of user programs
// make syscalls support multiple params