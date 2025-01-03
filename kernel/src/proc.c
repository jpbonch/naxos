#include "proc.h"
#include "puts.h"

#define PGSIZE 4096

#define INITIAL_PAGES 10 // hihgest addr is 0xFFFFFFFF

struct page {
    struct page* next;
} page;

struct page* freelist = 0;

struct proc* curproc = 0;

int pid = 0;

struct proc proctable[MAX_PROCS];

extern char _binary____build_init_elf_start[];
extern char _binary____build_init_elf_end[];

void memcpy(char* src, char* dest, unsigned int size) {
    for (int i = 0; i < size; i++) {
        *(dest+i) = *(src+i);
    }
}

void memset(char* dest, unsigned int size, int val) {
    for (int i = 0; i < size; i++) {
        *(dest+i) = val;
    }
}

void free_page(char* addr) {
    struct page* newpage = (struct page*) addr;
    newpage->next = freelist;
    freelist = newpage;
    memset((char*)newpage, PGSIZE, 0);
}


void init_mem() {
    for (int i = 0x100000; i < 0x100000 + INITIAL_PAGES * PGSIZE; i += PGSIZE) {
        free_page((char*) i);
    }
    puts("Finished initializing memory\n");
}


char* alloc_page() {
    char* ret = (char*) freelist;
    freelist = freelist->next;
    puts("allocing %x\n", (int)ret);
    return ret;
}

void init_user() {
    struct proc* p = allocproc();
    char* newpage = alloc_page();
    char* stack = alloc_page();

    unsigned int size = (unsigned int)(_binary____build_init_elf_end - _binary____build_init_elf_start);
    memcpy(_binary____build_init_elf_start, newpage, size);

    Elf32_Ehdr* ehdr = (Elf32_Ehdr*) newpage;
    Elf32_Phdr* phdr = (Elf32_Phdr*) ((char*)ehdr + ehdr->e_phoff);

    for (int i = 0; i < ehdr->e_phnum; i++) {
    if (phdr[i].p_type == PT_LOAD) {
        char* src = (char*)ehdr + phdr[i].p_offset;
        char* dst = (char*) phdr[i].p_vaddr;
        memcpy(src, dst, phdr[i].p_filesz);

        if (phdr[i].p_memsz > phdr[i].p_filesz) {
            memset(dst + phdr[i].p_filesz, 0,
                   phdr[i].p_memsz - phdr[i].p_filesz);
        }
        }
    }

    p->eip = ehdr->e_entry;
    p->esp = (int)stack;
    p->state = RUNNABLE;
}

void scheduler() {
    while (1) {
        for (int i = 0; i < MAX_PROCS; i++) {
            if (curproc == 0 && proctable[i].state == RUNNABLE) {
                curproc = &proctable[i];

                curproc->state = RUNNING;

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

void exec(char* path) {

}