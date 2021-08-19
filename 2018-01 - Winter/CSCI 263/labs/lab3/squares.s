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

sqrtr:                           # recursive part
    div.s $f2, $f0, $f1     # f1 = ((f0 / f1)+f1)/2
    add.s $f1, $f1, $f2
    div.s $f1, $f1, $f3
    c.eq.s $f1, $f4         # if (f1 = f4)--> same f1 twice jump endsqrt
    bc1t esqrt
    add.s $f4, $f5, $f1     # else f4 = f1
    j sqrtr

esqrt:   add.s $f0, $f5, $f1     # set f0 = f1 as stated in contract
    # restore $f1, $f2, $f3, $f4
    lwc1 $f1, 12($sp)
    lwc1 $f2, 8($sp)
    lwc1 $f3, 4($sp)
    lwc1 $f4, 0($sp)
    addi $sp, $sp, 16

    jr $ra                   # return f0
