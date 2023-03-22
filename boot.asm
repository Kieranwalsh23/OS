[ bits 16 ]
[ org 0x7C00 ]

; call the boot_init function
call boot_init
; call the kernel_load function
call kernel_load
; call the switch_to_32bit function to switch to 32 bit mode
call switch_to_32bit

; initialize the boot
boot_init:
    ; pop BX since we are messing with the stack
    pop BX
    ; set the KERNEL_ADDR to 0x1000
    KERNEL_ADDR equ 0x1000
    ; set BP (Base Pointer) to 0x9000
    mov BP, 0x9000
    ; set SP (Stack Pointer) to 0x9000
    mov SP, BP
    ; set the boot drive to the drive passed in
    mov [ BOOT_DRIVE ], dl
    ; jump to BX 
    jmp BX

; include necessary files
%include "gdt.asm"
%include "disk_read.asm"
%include "print_string.asm"
%include "switch_modes.asm"

; Pad the rest of the sector with 0's
times 510-($-$$) db 0
; Set the boot signature
dw 0xaa55
