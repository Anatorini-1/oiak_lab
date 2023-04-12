.global _start

SYS_SUCCESS = 0
SYS_EXIT = 1
SYSCALL = 0x80

SYS_WRITE = 4
STD_OUT = 1


.data`
    msg: .ascii "Witamy w koloni\n"
    msg_len = . - msg

.text
_start:
    mov $SYS_WRITE, %eax
    mov $STD_OUT, %ebx
    mov $msg, %ecx
    mov $msg_len, %edx
    int $SYSCALL

    mov $SYS_EXIT,%eax
    mov $SYS_SUCCESS, %ebx
    int $SYSCALL
    
