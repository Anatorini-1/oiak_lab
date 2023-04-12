.global _start

SYS_EXIT = 1
SYS_SUCCESS = 0
SYS_CALL = 0x80


SYS_WRITE = 4
STD_OUT = 1

.data
	liczba1: 
        .long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
    liczba2:
    	.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031

    
    

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
        push %ebx
        dec %esi
        jnz loop

    pushf


    mov $SYS_EXIT, %eax
    mov $SYS_SUCCESS, %ebx
    int $SYS_CALL
    
