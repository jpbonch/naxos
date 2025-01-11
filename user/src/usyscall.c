#include "usyscall.h"

int exec(char* path) {
    int ret;
    asm volatile("int $0x80" : "=a"(ret) : "a"(1), "b"(path)); // 1 is exec
    return ret;
}