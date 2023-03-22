; create print label
print:
    ; push all registers
    pusha
    ; set AH register to tty output
    mov AH, 0x0e

; Create loop label
loop:
    ; get the character at the address in BX
    mov AL, [ BX ]
    ; check if we are at the end of the string
    cmp AL, 0
    ; if we are at the end of the string, jump to done_loop
    je done_loop
    ; print the character
    int 10h
    ; increment BX
    add BX, 1
    ; jump back to loop
    jmp loop

; Create label for when we done the loop
done_loop:
    ; pop all registers
    popa
    ; return to caller
    ret