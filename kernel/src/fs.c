#include "fs.h"
#include "puts.h"

struct fsheader {
    int numfiles;
    int fsizes[MAXFILES];
    char fnames[MAXFILES][11];
    char* contents;
} header;

void init_fs() {
    header = *(struct fsheader*)(FS_ADDR);
}

char* get_contents(char* path) {
    puts("path: ");
    puts(path);
    puts("\n");
    unsigned int cumulative_size = 0;
    for (int i = 0; i < header.numfiles; i++) {
        puts("header fname: ");
        puts(header.fnames[i]);
        puts("\n");
        if (strcmp(header.fnames[i], path) == 0) {
            return header.contents + cumulative_size;
        }
        cumulative_size += header.fsizes[i];
    }
    return 0;
}