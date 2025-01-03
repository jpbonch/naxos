#ifndef PROC
#define PROC

#define MAX_PROCS 16

void init_user();
void init_mem();
char* alloc_page();
void scheduler();
struct proc* allocproc();

enum procstate { UNUSED, RUNNABLE, RUNNING };

typedef struct proc {
    int pid;
    enum procstate state; 
    int eip;
    int esp;
} proc;

// Example ELF definitions (simplified)
typedef unsigned int   Elf32_Addr;
typedef unsigned int   Elf32_Off;
typedef unsigned short Elf32_Half;
typedef unsigned int   Elf32_Word;

#define PT_LOAD 1

// Minimal ELF header
typedef struct {
    unsigned char e_ident[16];  // includes 0x7F, 'E', 'L', 'F'
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;   // <--- entry point virtual address
    Elf32_Off     e_phoff;   // <--- program header table offset (bytes into file)
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;   // <--- number of program headers
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

// Minimal program header
typedef struct {
    Elf32_Word p_type;   // PT_LOAD, etc.
    Elf32_Off  p_offset; // offset in file
    Elf32_Addr p_vaddr;  // virtual address to load to
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz; // size in file
    Elf32_Word p_memsz;  // total mem size (filesz + zero-filled region)
    Elf32_Word p_flags;
    Elf32_Word p_align;
} Elf32_Phdr;


#endif

