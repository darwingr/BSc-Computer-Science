  .data
def:     .float 2.0              # define immediate real operands
def2:    .float -1.0
def3:    .float 0.0
prompt1: .asciiz "Enter a real number (coefficient a): "
prompt2: .asciiz "Enter a real number (coefficient b): "
prompt3: .asciiz "Enter a real number (coefficient c): "
errmsg:  .asciiz "The solution is complex! "
solu:    .asciiz "The solutions are: "

  .text
main:
    # save $ra
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    lwc1 $f5, def3($0)      # f5 = 0

    # accept input
    la $a0, prompt1
    addi $v0, $0, 4         # Print prompt1 string
    syscall
    addi $v0, $0, 6         # Read float
    syscall
    add.s $f6, $f5, $f0     # f6 = a(input float)

    la $a0, prompt2
    addi $v0, $0, 4         # Print prompt2 string
    syscall
    addi $v0, $0, 6         # Read float
    syscall
    add.s $f7, $f5, $f0     # f7 = b(input float)

    la $a0, prompt3
    addi $v0, $0, 4         # Print prompt3 string
    syscall
    addi $v0, $0, 6         # Read float
    syscall
    add.s $f8, $f5, $f0     # f8 = c(input float)

    # check b^2 - 4*a*c
    mul.s $f9, $f7, $f7     # f9 = b * b
    mul.s $f10, $f6. $f8    # f10 = a * c
    add.s $f10, $f10, $f10  # f10 = 4 * a * c
    add.s $f10, $f10, $f10

    c.lt.s $f9, $f10        # if (f9 < f10)-->  jump err
    bc1t err

    sub.s $f0, $f9, $f10    # f0 = b^2 - 4*a*c

    jal sqrt                # call square root function

    lwc1 $f9, def2($0)      # f9 = -1.0
    mul.s $f7, $f7, $f9     # f7 = f7 * (-1.0)
    add.s $f10, $f7, $f0    # f10 = f7 + f0
    sub.s $f11, $f7, $f0    # f11 = f7 - f0
    lwc1 $f9, def($0)
    mul.s $f6, $f6, $f9     # f6 = f6 * 2

    div.s $f10, $f10, $f6   # f10 = f10/f6
    div.s $f11, $f11, $f6   # f11 = f11/f6

    la   $a0, solu($0)      # print solu string
    addi $v0, $0, 4
    syscall

    lwc1 $f12, def3($0)     # f12 = 0
    add.s $f12, $f12, $f10
    addi $v0, $0, 2         # Print float
    syscall

    addi $v0, $0, 11        # print space
    addi $a0, $0, 32
    syscall

    lwc1 $f12, def3($0)     # f12 = 0
    add.s $f12, $f12, $f11
    addi $v0, $0, 2         # Print float
    syscall

    j quit

err:
    la $a0, errmsg
    addi $v0, $0, 4         # Print errmsg string
    syscall

    # restore $ra
quit:
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

#---------------------------------------------------------------------------
# Square Root Function: This function returns the square
# root of a number passed in $f0. Returned number is stored
# in f0. This method works recursively without need for
# storing previous variables.
#
# args: $f0 --> number to get the sqrt of
# Consumes: f0, f1, f2, f3, f4
# Returns: f0
#---------------------------------------------------------------------------
sqrt:
    # store $f1, $f2, $f3, $f4
    addi $sp, $sp, -16
    swc1 $f1, 12($sp)
    swc1 $f2, 8($sp)
    swc1 $f3, 4($sp)
    swc1 $f4, 0($sp)

    # program starts here
    lwc1 $f1, def($0)       # f1 = 2
    lwc1 $f5, def3($0)      # f5 = 0
    add.s $f3, $f5, $f1     # f1 = f3 = 2
    c.eq.s $f0, $f5         # if f0 != 0 start sqrt loop (sqrtr)
    bc1f sqrtr              # else :
    jr $ra                  # return 0 --> F12 is already 0

sqrtr:                      # recursive part
    div.s $f2, $f0, $f1     # f1 = ((f0 / f1)+f1)/2
    add.s $f1, $f1, $f2
    div.s $f1, $f1, $f3
    c.eq.s $f1, $f4         # if (f1 = f4)--> same f1 twice jump endsqrt
    bc1t esqrt
    add.s $f4, $f5, $f1     # else f4 = f1
    j sqrtr

esqrt:
    add.s $f0, $f5, $f1     # set f0 = f1 as stated in contract
    # restore $f1, $f2, $f3, $f4
    lwc1 $f1, 12($sp)
    lwc1 $f2, 8($sp)
    lwc1 $f3, 4($sp)
    lwc1 $f4, 0($sp)
    addi $sp, $sp, 16

    jr $ra                   # return f0
