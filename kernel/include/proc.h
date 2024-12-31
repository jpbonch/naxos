#ifndef PROC
#define PROC


void init_user();
void init_mem();
char* alloc_page();

typedef struct proc {
    int pid;
} proc;

#endif