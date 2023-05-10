
.global addInts


.data


.text
addInts:
    prologue:
    PUSH %ebp 
    MOV %esp, %ebp 
    sub $80, %esp 
    PUSH %edi 
    PUSH %esi 
    PUSH %ebx
    PUSH %ecx
    PUSH %edx
    
    MOV 8(%ebp), %edi  # W edi adres początku tablicy structur
    MOV 12(%ebp), %ecx # W ecx długość tablicy struktur
    XOR %esi, %esi



    mainLoop:
        push %ecx
        mov $4, %ecx
        xor %ebx, %ebx
        push %ecx
        rdtscp
        pop %ecx
        push %eax
        push %edx
        innerLoop:
            add (%edi), %ebx
            add $4, %edi
        loop innerLoop
        push %ecx
        rdtscp
        pop %ecx
        pop %ebx
        sub %ebx, %edx
        pop %ebx
        sub %ebx, %eax
        add %eax, %esi

        pop %ecx
        loop mainLoop

    MOV %esi, %eax    


    epilogue:
    pop %edx
    pop %ecx
    pop %ebx 
    pop %esi 
    pop %edi 
    leave 
    ret 


