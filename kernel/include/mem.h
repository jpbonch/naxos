#ifndef MEM
#define MEM

#define PGSIZE 1048576 // 1MB
#define INITIAL_PAGES 10 // hihgest addr is 0xFFFFFFFF

void memcpy(char* src, char* dest, unsigned int size);
void memset(char* dest, unsigned int size, int val);
void free_page(char* addr);
void init_mem();
char* alloc_page();

#endif