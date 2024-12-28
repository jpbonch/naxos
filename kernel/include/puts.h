#ifndef PUTS
#define PUTS

char *vga;
void init_vga();
void putc(char c);
void puts(const char* str, ...);
void putint(int num);

#endif