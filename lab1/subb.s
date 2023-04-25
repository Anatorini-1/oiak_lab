.global _start

SYS_EXIT = 1
SYS_SUCCESS = 0
SYS_CALL = 0x80


SYS_WRITE = 4
STD_OUT = 1

.data
	liczba1: 
        .long 0x20001000, 0x20000000, 0x00000010, 0x00000001
    liczba2:
    	.long 0x11111111, 0x11111111, 0x11111111, 0x11111111

    
    
.text
_start:

    mov $liczba1, %ecx
    mov $liczba2, %edx
    sub $4, %ecx
    sub $4, %edx
    mov $4, %esi

    loop:
        mov (%ecx,%esi,4), %eax 
        mov (%edx,%esi,4), %ebx
        sbb %eax,%ebx
        pushl %ebx
        dec %esi
        jnz loop
    
    jc overflow
    
    noOverflow:
        pushl $0
        jmp exit

    overflow:
        pushl $-1
    
    exit:
        mov $SYS_EXIT, %eax
        mov $SYS_SUCCESS, %ebx
        int $SYS_CALL
    
