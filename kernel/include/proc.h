#ifndef PROC
#define PROC

#define MAX_PROCS 16

void init_user();
void init_mem();
char* alloc_page();
void scheduler();
struct proc* allocproc();

enum procstate { UNUSED, RUNNABLE, RUNNING };

typedef struct proc {
    int pid;
    enum procstate state; 
    int eip;
    int esp;
    char* pagestart;
} proc;

#endif

