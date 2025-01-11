#ifndef FS
#define FS


#define FS_ADDR 0x5800

#define MAXFILES 16

void init_fs();


typedef struct file {
    int fsize;
    char fname[11];
    char* contents;
} file;

struct file get_file(char* path);

typedef struct fsheader {
    int numfiles;
    int fsizes[MAXFILES];
    char fnames[MAXFILES][11];
    unsigned char contents[];
} fsheader;

struct fsheader* header;



#endif