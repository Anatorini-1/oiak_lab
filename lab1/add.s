.global _start

SYS_EXIT = 1
SYS_SUCCESS = 0
SYS_CALL = 0x80


SYS_WRITE = 4
STD_OUT = 1

.data
	liczba1: 
        .long 0xF0000010, 0x00000100, 0x00001000, 0xF0000000
    liczba2:
    	.long 0x10000010, 0x00000100, 0x00001000, 0x20000000

    
    
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
        adc %eax,%ebx
        pushl %ebx
        dec %esi
        jnz loop
    
    jc overflow
    
    noOverflow:
        pushl $0
        jmp exit

    overflow:
        pushl $1
    
    exit:
        mov $SYS_EXIT, %eax
        mov $SYS_SUCCESS, %ebx
        int $SYS_CALL
    
