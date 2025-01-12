#include "idt.h"
#include "syscall.h"

struct IDTEntry {
    unsigned short offset_low;    // Lower 16 bits of handler address
    unsigned short selector;      // Kernel code segment selector
    unsigned char  zero;          // Always zero
    unsigned char  type_attr;     // Type and attributes (e.g., 0x8E for interrupt gate)
    unsigned short offset_high;   // Upper 16 bits of handler address
} __attribute__((packed));

struct IDTEntry idt[256];   // IDT with 256 entries

void set_idt_entry(int vector, int (*handler)(), unsigned short selector, unsigned char type_attr) {
    idt[vector].offset_low = (unsigned short)((unsigned int)handler & 0xFFFF);
    idt[vector].selector = selector;
    idt[vector].zero = 0;
    idt[vector].type_attr = type_attr;
    idt[vector].offset_high = (unsigned short)(((unsigned int)handler >> 16) & 0xFFFF);
}

void load_idt() {
    set_idt_entry(0x80, syscall_handler, 0x08, 0x8E);

    struct {
        unsigned short limit;    // Size of IDT
        unsigned int base;     // Base address of IDT
    } __attribute__((packed)) idt_descriptor = {
        .limit = sizeof(idt) - 1,
        .base = (unsigned int)&idt,
    };

    asm volatile ("lidt %0" : : "m"(idt_descriptor));

    asm volatile ("sti");
}