.global _start

SYS_SUCCESS = 0
SYS_EXIT = 1
SYSCALL = 0x80

SYS_WRITE = 4
STD_OUT = 1

SYS_READ = 3
STD_IN = 0


.data
    buffer:  .ascii "    "
    buffer_len = . - buffer
    
.text
    text1: .ascii "1111"
    equal: .ascii "EQUAL\n"
    el =  .- equal
    diff: .ascii "DIFFERENT\n"
    dl = . - diff
_start:

#Write text from STDIN into buffer
    MOV $SYS_READ, %eax 
    MOV $STD_IN, %ebx
    MOV $buffer, %ecx
    MOV $buffer_len,%edx
    INT $SYSCALL

#Prepare registers for comparing strings
    MOV $text1, %ebx #Write the address of the sample text to ebx
    MOV $buffer, %ecx#Write the address of the buffer to ecx
    MOV $4, %esi     #The strings are 4 bytes long, so write 4 to esi, as the loop counter

loop: #Check strings character by character
    MOVb (%ebx), %al #Load first byte from ebx to al
    MOV (%ecx), %dl  #Load first byte from ecx to dl
    CMP %al, %dl     #Compare al to dl, set EFLAGS
    JNE diffrent     #If al != dl => JUMP to "different"
    INC %ebx         #Increment ebx, moving to the next byte of sample text
    INC %ecx         #Increment ecx, moving to the next byte of the buffer
    DEC %esi         #Decrement esi, the loop counter
    JNZ loop         #Loop while esi > 0

same: #If strings are equal, write "EQUAL" to std_out and exit 
    MOV $SYS_WRITE, %eax    
    MOV $STD_OUT, %ebx
    MOV $equal, %ecx
    MOV $el, %edx
    INT $SYSCALL
    JMP exit

diffrent: #If strings are different, write "DIFFERENT" to std_out
    #do smth
    MOV $SYS_WRITE, %eax
    MOV $STD_OUT, %ebx
    MOV $diff, %ecx
    MOV $dl, %edx
    INT $SYSCALL

exit: #exit with error_code 0
    MOV $SYS_EXIT,%eax
    MOV $SYS_SUCCESS, %ebx
    INT $SYSCALL
