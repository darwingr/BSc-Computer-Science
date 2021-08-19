# mulu.s
# -------
# Lab #6 - Integer Multiplication and Division
#
# Author: Darwin Jacob Groskleg
# Class:  CSCI 263
# Date:   Saturday, April 7th, 2018
#
# Purpose: Learn how to implement integer multiplication and division without
# using the built-in DIV, DIVU, MUL, or MULU instructions.
#
# Write a function that performs unsigned integer multiplication without using
# the built-in MULU instruction. Provided is skeleton of code. You are to write
# the body of the function. You are also asked to compare with the built-in
# instructions.
#
# Reminder: a * b = c
#   a is the Multiplier
#   b is the Multiplicand
# OR
#       A <- Multiplicand
#     x B <- Multiplier
#    -----
#       C
#
# Console Sample:
# -----------------------------------------------------------------------------
# (spim) load "mulu.s"
# (spim) run
# This program does AxB without using multu or div
# Please enter the first number (multiplier): 4
# Please enter the second number (multiplicand): 54
# The product, using my program is: 0 216
# The product, using MIPS multu is: 0 216
# (spim) run
# This program does AxB without using multu or div
# Please enter the first number (multiplier): 78  
# Please enter the second number (multiplicand): 22
# The product, using my program is: 0 1716
# The product, using MIPS multu is: 0 1716
# -----------------------------------------------------------------------------

.data

promptStart:    .asciiz "This program does AxB without using multu or div"
getA:           .asciiz "Please enter the first number (multiplier): "
getB:           .asciiz "Please enter the second number (multiplicand): "
space:          .asciiz " "
result:         .asciiz "The product, using my program is: "
mipMult:        .asciiz "The product, using MIPS multu is: "
endLine:        .asciiz "\n"

.text

main:
    #"welcome" screen
    li  $v0, 4             # code for print_string
    la  $a0, promptStart   # point $a0 to prompt string
    syscall                # print the prompt

    li  $v0, 4          # code for print_string
    la  $a0, endLine    # point $a0 to prompt string
    syscall             # print the prompt

    #prompt for multiplier
    li  $v0, 4          # code for print_string
    la  $a0, getA       # point $a0 to prompt string
    syscall             # print the prompt

    #acquire multiplier
    li   $v0, 5         # code for read_int
    syscall             # get an int from user --> returned in $v0
    move $s0, $v0       # move the resulting int to $s0

    #prompt for multiplicand
    li  $v0, 4          # code for print_string
    la  $a0, getB       # point $a0 to prompt string
    syscall             # print the prompt

    #acquire multiplicand
    li   $v0, 5         # code for read_int
    syscall             # get an int from user --> returned in $v0
    move $s1, $v0       # move the resulting int to $s0

    # Save copies for later
    move $s5, $s0       # copy of multiplicand to use in multu
    move $s6, $s1       # copy of multiplier to use in multu

    jal MyMult
    j   print


# Print Procedure, needs result in v0
print:
    # print result string
    li  $v0, 4          # code for print_string
    la  $a0, result     # point $a0 to string
    syscall             # print the result string

    # print out the result
    li   $v0, 1         # code for print_int
    move $a0, $s4       # put result in $a0
    syscall             # print out result

    li  $v0, 4          # code for print_string
    la  $a0, space      # point $a0 to string
    syscall             # print the result string

    li   $v0, 1         # code for print_int
    move $a0, $s3       # put result in $a0
    syscall             # print out result

    # print the line feed
    li  $v0, 4          # code for print_string
    la  $a0, endLine    # point $a0 to string
    syscall             # print the linefeed

doMult:
    # Do same computation using the built-in Multu instructions
    multu $s5, $s6      # use multu
    mfhi  $t0           # read HI out
    mflo  $t1           # read LO out

    li  $v0, 4          # code for print_string
    la  $a0, mipMult    # point $a0 to string
    syscall

    # print out the hi result
    li   $v0, 1         # code for print_int
    move $a0, $t0       # put high in $a0
    syscall             # print out result

    li  $v0, 4          # code for print_string
    la  $a0, space      # point $a0 to string
    syscall             # print the result string

    # print out the lo result
    li   $v0, 1         # code for print_int
    move $a0, $t1       # put low in $a0
    syscall             # print out result

    # print the line feed
    li  $v0, 4          # code for print_string
    la  $a0, endLine    # point $a0 to string
    syscall             # print the linefeed

exit:
    # All done, thank you!
    li  $v0, 10         # code for exit
    syscall             # exit program


# Multiplier Procedure :
# Implements the Shift-and-Add algorithm to calculate the product of two
# unsigned integers (not Booth's algorithm). Result requires twice the space to
# store as either inputs.
#
# args: none
# returns: nothing
#
# Consumes: s0 – s4
#   s0 multiplier
#   s1 multiplicand (lw)
#   (s2 -> multiplicand, hw)
MyMult:
    move $s3, $0        # lw product
    move $s4, $0        # hw product

    beq  $s1, $0, done
    beq  $s0, $0, done

    move $s2, $0        # extend multiplicand to 64 bits

loop:
    andi $t0, $s0, 1    # t0 = LSB(multiplier)
    beq  $t0, $0, next  # skip if zero
    addu $s3, $s3, $s1  # lw(product) += lw(multiplicand)
    sltu $t0, $s3, $s1  # catch carry-out(0 or 1)
    addu $s4, $s4, $t0  # hw(product) += carry
    addu $s4, $s4, $s2  # hw(product) += hw(multiplicand)

next:
    # shift multiplicand left
    srl  $t0, $s1, 31   # copy bit from lw to hw (srl: shift right logical)
    sll  $s1, $s1, 1    # shift lw(multiplicand) left
    sll  $s2, $s2, 1    # shift hw(multiplicand) left
    addu $s2, $s2, $t0

    srl  $s0, $s0, 1    # shift multiplier right
    bne  $s0, $0, loop  # if $S0 not 0, go back to the loop

done:
    jr $ra
