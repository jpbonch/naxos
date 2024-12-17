BITS 16            ; Set to 16-bit mode for x86 real mode
GLOBAL _start      ; Make _start visible to the linker
EXTERN main

SECTION .text
_start:
    cli

    ; Set up segment registers
    xor ax, ax           ; Clear AX register
    mov ds, ax           ; Set Data Segment to 0
    mov es, ax           ; Set Extra Segment to 0
    mov ss, ax           ; Set Stack Segment to 0
    mov sp, 0x7C00       ; Set stack pointer to 0x7C00

    call print_message
    
    ; call main

    halt

print_message:
    mov si, msg          ; Load address of message into SI
.print_char:
    lodsb                ; Load next byte from [SI] into AL
    cmp al, 0            ; Check if end of string (null terminator)
    je .done             ; If zero, we're done
    mov ah, 0x0E         ; BIOS teletype output function
    int 0x10             ; Call BIOS interrupt to print character
    jmp .print_char      ; Loop to print next character
.done:
    mov ah, 0x0E         ; BIOS teletype output function
    int 0x10             ; Call BIOS interrupt to print character
    ret

msg db 'Booting...', 0x0D, 0xA, 0       ; Message to display, null-terminated

times 510-($-$$) db 0     ; Fill rest of boot sector with 0s
dw 0xAA55                 ; Boot signature
