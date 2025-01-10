#include "exec.h"
#include "syscall.h"
#include "puts.h"

typedef int (*syscall_t)(char*); 

syscall_t syscalls[] = {
    exec
};

int syscall_handler() {
    int syscall_number;
    char* arg1;

    asm volatile("mov %%eax, %0" : "=r"(syscall_number)); 
    asm volatile("mov %%ebx, %0" : "=r"(arg1));

    return exec(arg1);
    // return syscalls[syscall_number](arg1);
}