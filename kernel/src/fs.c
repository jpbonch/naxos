#include "fs.h"
#include "puts.h"
#include "mem.h"

void init_fs() {
    header = (struct fsheader*)FS_ADDR;
}

struct file get_file(char* path) {
    struct file f;
    unsigned int cumulative_size = 0;
    for (int i = 0; i < header->numfiles; i++) {
        if (strcmp(header->fnames[i], path) == 0) {
            f.contents = header->contents + cumulative_size;
            memcpy(f.fname, header->fnames[i], 11);
            f.fsize = header->fsizes[i];
            return f;
        }
        cumulative_size += header->fsizes[i];
    }
    return f;
}