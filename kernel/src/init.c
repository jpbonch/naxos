//#include "syscall_nums.h"

// should be run in user mode and syscall to exec
int main() {
    // exec("init"); //should be syscall
    __asm__ __volatile__(
        "movl $1, %%eax; movl $init, %%ebx; int $0x80; init: .string \"init\\0\";"
        :
        :
        : "eax", "ebx"
    );

    return 0;
}