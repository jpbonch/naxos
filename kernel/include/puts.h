#ifndef PUTS
#define PUTS

char *vga;
void init_vga();
void putc(char c);
void puts(const char* str, ...);
void putint(int num);
int strcmp(char* s1, char* s2);

#endif