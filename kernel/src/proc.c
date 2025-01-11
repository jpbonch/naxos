#include "proc.h"
#include "puts.h"
#include "mem.h"
#include "elf.h"

struct proc* curproc = 0;
int pid = 0;
struct proc proctable[MAX_PROCS];

extern char _binary____build_uinit_elf_start[];
extern char _binary____build_uinit_elf_end[];


void init_user() {
    struct proc* p = allocproc();
    char* newpage = alloc_page();
    char* stack = alloc_page();

    unsigned int size = (unsigned int)(_binary____build_uinit_elf_end - _binary____build_uinit_elf_start);
    memcpy(newpage, _binary____build_uinit_elf_start, size);

    Elf32_Ehdr* ehdr = (Elf32_Ehdr*) newpage;
    load_elf(ehdr);

    p->eip = ehdr->e_entry;
    p->esp = (unsigned int)stack + PGSIZE - 1;
    p->pagestart = newpage;
    p->stackpage = stack;
    p->state = RUNNABLE;
}

void scheduler() {
    while (1) {
        for (int i = 0; i < MAX_PROCS; i++) {
            if (curproc == 0 && proctable[i].state == RUNNABLE) {
                curproc = &proctable[i];

                curproc->state = RUNNING;
                puts("Scheduler pagestart %x\n",  curproc->pagestart);
                puts("scheduler jumping to %x\n", curproc->eip);

                asm volatile(
                    "movl %0, %%esp\n" // Set stack pointer
                    "jmp *%1\n"        // Jump to the entry point (user code)
                    :
                    : "r"(curproc->esp), "r"(curproc->eip)
                );

                
            }
        }
    }
}

struct proc* allocproc() {
    for (int i = 0; i < MAX_PROCS; i++) {
        if (proctable[i].state == UNUSED) {
            proctable[i].pid = pid++;
            return &proctable[i];
        }
    }
    return 0;
}

void load_elf(Elf32_Ehdr* ehdr) {
    Elf32_Phdr* phdr = (Elf32_Phdr*) ((char*)ehdr + ehdr->e_phoff);

    for (int i = 0; i < ehdr->e_phnum; i++) {
    if (phdr[i].p_type == PT_LOAD) {
        char* src = (char*)ehdr + phdr[i].p_offset;
        char* dst = (char*) phdr[i].p_vaddr;
        memcpy(dst, src, phdr[i].p_filesz);

        if (phdr[i].p_memsz > phdr[i].p_filesz) {
            memset(dst + phdr[i].p_filesz, 0,
                   phdr[i].p_memsz - phdr[i].p_filesz);
        }
        }
    }
}
