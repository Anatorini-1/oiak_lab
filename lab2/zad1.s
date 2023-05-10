.global _start


.data

    minus1: .int -1
    ten: .int 10

.text
_start:
    //Sqrt(-1) = NaN
    FILD (minus1)
    FSQRT

    //10 / 0 = +INF
    FLDZ
    FILD (ten)
    FDIVP

    //-10 / 0 = -INF
    FLDZ
    FILD (ten)
    FCHS
    FDIVP

    //0 == 0
    FLDZ

    //0 * -1 == -0

    FLDZ
    FCHS


exit:
    mov $1, %eax
    mov $0, %ebx
    int $0x80
