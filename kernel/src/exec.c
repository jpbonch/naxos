#include "exec.h"
#include "elf.h"
#include "proc.h"
#include "mem.h"
#include "puts.h"
#include "fs.h"

extern struct proc* curproc;

int exec(char* path) {

    struct file f = get_file(path);

    memset(curproc->pagestart, PGSIZE, 0);
    memcpy(curproc->pagestart, f.contents, f.fsize);

    curproc->eip = (unsigned int)curproc->pagestart;

    curproc->esp = (unsigned int)(curproc->stackpage) + PGSIZE - 1;
    puts("eip jumping to: %x\n", curproc->eip);

    asm volatile(
        "movl %0, %%esp\n"
        "jmp *%1\n"
        :
        : "r"(curproc->esp), "r"(curproc->eip)
    );
    
    return 0;
}
