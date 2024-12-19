SECTIONS {
    . = 0x1000;           /* Load address */
    .text : { *(.text) }  /* Code */
    .rodata : { *(.rodata) } /* Read-only data (strings) */
    .data : { *(.data) }  /* Writable data */
    .bss : { *(COMMON) *(.bss) } /* Uninitialized data */
}
