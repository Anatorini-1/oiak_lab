.global _start


.data
    msg: .ascii "Txt\n"
    msg_len = . - msg
    liczba1: .float 3.5
    liczba2: .float 2.5
    liczba3: .float 8.75

.text

_start:

add:
    FLDs (liczba1)
    FLDs (liczba2)
    FADDP
    
    jmp exit

sub:

    jmp exit

mul:

    jmp exit

div:

    jmp exit





exit:
    mov $1, %eax
    mov $0, %ebx
    int $0x80
