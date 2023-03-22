; Switch to 32-bit mode
switch_to_32bit:
    cli                     ; Turn off interrupts
    lgdt [gdt_descriptor]	; load the gdt descriptor
    mov eax, cr0            ; move control register contents to 32 bit register
    or eax, 0x1             ; Turn on the first bit
    mov cr0, eax            ; Move contents back to control register
    jmp CODE_SEGMENT_INDEX:begin_32bit_mode ; Code Index = 0x08
    ;ret
[ bits 32 ]
begin_32bit_mode:
    mov ax, DATA_SEGMENT_INDEX	; 0x10 for data selector
    mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
    mov gs, ax
    ; Set 32 bit base/stack pointers
    mov EBP, 0x90000
    mov ESP, EBP
    ; Jump to Kernel Address
    jmp KERNEL_ADDR
    
