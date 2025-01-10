#include "syscall_nums.h"

int exec(char* path) {
    int ret;
    asm volatile("int $0x80" : "=a"(ret) : "a"(SYS_EXEC), "b"(path));
    return ret;
}