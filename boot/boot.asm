[org 0x7c00]   
[bits 16]
KERNEL_LOCATION equ 0x1000

GLOBAL _start      ; Make _start visible to the linker

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

mov [BOOT_DISK], dl    

_start:
    ; Set up segment registers
    xor ax, ax           ; Clear AX register
    mov ds, ax           ; Set Data Segment to 0
    mov es, ax           ; Set Extra Segment to 0
    mov ss, ax           ; Set Stack Segment to 0
    mov bp, 0x8000
    mov sp, 0x7C00       ; Set stack pointer to 0x7C00

    mov bx, KERNEL_LOCATION
    mov dh, 0x36   ; 54 Sectors to read, first 36 kernel next 18 fs

    mov ah, 0x02
    mov al, dh 
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13      

    mov ah, 0x0
    mov al, 0x3
    int 0x10          
    
    cli
    lgdt [GDT_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:start_protected_mode

    jmp $

msg db 'Booting...', 0x0D, 0xA, 0       ; Message to display, null-terminated

BOOT_DISK: db 0

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0xA0000		; 32 bit stack base pointer
	mov esp, ebp

    jmp KERNEL_LOCATION
times 510-($-$$) db 0     ; Fill rest of boot sector with 0s
dw 0xAA55                 ; Boot signature
