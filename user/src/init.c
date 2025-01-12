#include "usyscall.h"

int main() {
    // int pid = fork();
    // if (pid == 0) {
    //     exec("sh");
    // }
    *((char*)0xB8000) = 'X';
    *((char*)0xB8002) = 'X';
    fork();
    while(1){}
    return 0;
}

__attribute__((noreturn))
void _start(void) {
    main();
    for (;;) { }
}

