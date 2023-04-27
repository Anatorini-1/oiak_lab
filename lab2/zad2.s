.global _start


.data
    liczba1: .float 6
    liczba2: .float 2
    liczba3: .float 8.75
    zero: .float 0
    buffer: .int 255
    double_even: .int    0b0000001001111111
    double_nInf: .int    0b0000011001111111
    double_pInf: .int    0b0000101001111111
    double_Trun: .int    0b0000111001111111
    float_even: .int     0b0000000001111111
    float_nInf: .int     0b0000010001111111
    float_pInf: .int     0b0000100001111111
    float_Trun: .int     0b0000110001111111
    extDouble_even: .int 0b0000001101111111
    extDouble_nInf: .int 0b0000011101111111
    extDouble_pInf: .int 0b0000101101111111
    extDouble_Trun: .int 0b0000111101111111


.text

_start:


.setPrecision:
    //FLDCW (double_even)
    //FLDCW (double_nInf)
    //FLDCW (double_pInf)
    //FLDCW (double_Trun)

    //FLDCW (float_even)
    //FLDCW (float_nInf)
    FLDCW (float_pInf)
    //FLDCW (float_Trun)

    //FLDCW (extDouble_even)
    //FLDCW (extDouble_nInf)
    //FLDCW (extDouble_pInf)
    //FLDCW (extDouble_Trun)


.loadOperands:
    FLDs (liczba1)
    FLDs (liczba2)

.math:
    FDIVP





exit:
    mov $1, %eax
    mov $0, %ebx
    int $0x80
