#include "proc.h"
#include "puts.h"

#define PGSIZE 4096

struct page {
    struct page* next;
} page;

struct page* freelist = 0;

void free_page(char* addr) {
    // todo: clear page to remove dangling refs
    struct page* newpage = (struct page*) addr;
    newpage->next = freelist;
    freelist = newpage;
}


void init_mem() {
    for (int i = 0x4000; i < 0x6000; i += PGSIZE) {
        puts("Freeing page %d\n", i);
        free_page((char*) i);
    }
}


char* alloc_page() {
    char* ret = (char*) freelist;
    freelist = freelist->next;
    // puts("allocing %d", (int)ret);
    return ret;
}


void init_user() {

}

void allocproc() {

}

void exec(char* path) {

}