#ifndef FS
#define FS


#define FS_ADDR 0x3000

#define MAXFILES 16

void init_fs();
char* get_contents(char* path);




#endif