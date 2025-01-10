#include "exec.h"
#include "elf.h"
#include "proc.h"
#include "mem.h"
#include "puts.h"
#include "fs.h"

extern struct proc* curproc;

int exec(char* path) {
    // copy elf to current page
    // what to do with eip and esp?
    puts("pagestart %x\n", (int)curproc->pagestart);

    char* contents = get_contents(path);

    puts("contents start: %d\n", (int) contents);

    // asm volatile(
    //     "movl %0, %%esp\n" // Set stack pointer
    //     "jmp *%1\n"        // Jump to the entry point (user code)
    //     :
    //     : "r"(curproc->esp), "r"(curproc->eip)
    // );
    
    // Elf32_Ehdr* ehdr;
    // load_elf(ehdr);
    return 0;
}
