#include "mem.h"
#include "puts.h"

struct page {
    struct page* next;
} page;

struct page* freelist = 0;

void free_page(char* addr) {
    memset(addr, PGSIZE, 0);
    struct page* newpage = (struct page*) addr;
    newpage->next = freelist;
    freelist = newpage;
    
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

void memcpy(char* dest, char* src, unsigned int size) {
    for (int i = 0; i < size; i++) {
        *(dest+i) = *(src+i);
    }
}

void memset(char* dest, unsigned int size, int val) {
    for (int i = 0; i < size; i++) {
        *(dest+i) = val;
    }
}