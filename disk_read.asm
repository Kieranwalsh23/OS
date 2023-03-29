; disk_read label
kernel_load:
    ; Push registers incase we have data in registers that we need later
    pusha
    ; Set AH to read from the disk
    mov AH, 0x02
    ; Set AL to number of sectors from the drive we are going to load
    ; (((FileSize)-512)/512) Sectors
    mov AL, [ SECTOR_SIZE ]
    ; BX – Memory address to load the Kernel into (We have this stored in our KERNEL_ADDR)
    mov BX, KERNEL_ADDR
    ; CH – Cylinder. Set to 0x00
    mov CH, 0x00
    ; CL – Sector – starts at 0x02
    mov CL, 0x02
    ; DH – Head – Set to 0x00
    mov DH, 0x00
    ; DL – Drive Number, given to us by the BIOS
    mov DL, [ BOOT_DRIVE ]
    int 13h 
    ; Check if the disk read was successful
    jc disk_read_error
    ; Check if the disk sector was successful
    cmp AL, [ SECTOR_SIZE ]
    jne disk_sector_error
    ; Pop registers
    popa
    ; Return to the main program
    ret

; Print error message if disk read was unsuccessful
disk_read_error:
    ; move the error message to the BX register
    mov BX, READ_ERROR_MSG
    ; Call the print function
    call print
    ; Jump to the done label
    jmp done

; Print error message for disk sector error
disk_sector_error:
    ; move the error message to the BX register
    mov BX, SECTOR_ERROR_MSG
    ; Call the print function
    call print
    ; Jump to the done label
    jmp done

; create done label. Infinite loop
done:
    jmp $

; Data / Variables
BOOT_DRIVE DB 0
SECTOR_ERROR_MSG DB "SECTOR ERROR Message", 0
READ_ERROR_MSG DB "READ ERROR Message", 0
; (((FileSize)-512)/512) Sectors ==> 25 (decimal) ==> 0x19 (hex)
; Current File Size: 13,312 bytes
SECTOR_SIZE DB 0x19

