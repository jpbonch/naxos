void print(const char* str) {
    while (*str) {
        asm volatile (
            "movb %0, %%al\n"
            "movb $0x0E, %%ah\n"
            "int $0x10\n"
            :
            : "r"(*str)
            : "rax"
        );
        str++;
    }
}

void main() {
    print("Hello from the kernel!\n");
    while (1) { }
}