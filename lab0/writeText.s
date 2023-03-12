.global _start

SYS_SUCCESS = 0
SYS_EXIT = 1
SYSCALL = 0x80

SYS_WRITE = 4
STD_OUT = 1

SYS_READ = 3
STD_IN = 0


.data

    buffer:  .ascii "     "
    buffer_len = . -buffer


.text
    msg: .ascii "Write text(5): "
    msg_len = . - msg

    msg2: .ascii "\nWritten text: "
    msg2_len = . - msg2

    endl: .byte 10
    endl_len = . - endl

_start:
    mov $SYS_WRITE, %eax
    mov $STD_OUT, %ebx
    mov $msg, %ecx
    mov $msg_len, %edx
    int $SYSCALL

    mov $SYS_READ,%eax
    mov $STD_IN, %ebx
    mov $buffer, %ecx
    mov $buffer_len, %edx
    int $SYSCALL

    mov $SYS_WRITE, %eax
    mov $STD_OUT, %ebx
    mov $msg2, %ecx
    mov $msg2_len, %edx
    int $SYSCALL

    mov $SYS_WRITE, %eax
    mov $STD_OUT, %ebx
    mov $buffer, %ecx
    mov $buffer_len, %edx
    int $SYSCALL
    
    mov $SYS_WRITE, %eax
    mov $STD_OUT, %ebx
    mov $endl, %ecx
    mov $endl_len, %edx
    int $SYSCALL

    mov $SYS_EXIT,%eax
    mov $SYS_SUCCESS, %ebx
    int $SYSCALL
    
