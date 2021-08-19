# square.s
# ------------
# Lab #3 - Basic Functions in MIPS
#
# Author: Darwin Jacob Groskleg
# Class:  CSCI 263
# Date:   Saturday, April 7th, 2018
#
# Purpose:
# Implement a program in MIPS that calls a function to calculate the square of
# the next given integer value (a0 + 1). The program should return the next
# 5 squares of a given integer.
#
# Console Sample:
# -----------------------------------------------------------------------------
# (spim) load "square.s"
# (spim) run
# Enter an integer for N (positive): 2
# Enter the square of N (positive):  4
# The next 5 solutions (squares): 9 16 25 36 49
# (spim) run
# Enter an integer for N (positive): 2
# Enter the square of N (positive):  6
# The input is erroneous.
# (spim) run
# Enter an integer for N (positive): -3
# Enter the square of N (positive):  9
# The input is erroneous.
# -----------------------------------------------------------------------------

.data
prompt1:  .asciiz "Enter an integer for N (positive): "
prompt2:  .asciiz "Enter the square of N (positive):  "
errmsg:   .asciiz "The input is erroneous. "
solu:     .asciiz "The next 5 solutions (squares): "
endl:     .asciiz "\n"

.text
main:
    addi $sp, $sp, -4   # Increment the stack pointer
    sw   $ra, 0($sp)    # save $ra, the return address

    # Accept input 1
    la   $a0, prompt1
    addi $v0, $0, 4     # Print prompt1 string
    syscall
    addi $v0, $0, 5     # Read int
    syscall
    add  $s0, $v0, $0   # s0 = a(input int)

    # Accept input 2
    la   $a0, prompt2
    addi $v0, $0, 4     # Print prompt2 string
    syscall
    addi $v0, $0, 5     # Read int
    syscall
    add  $s1, $v0, $0   # s1 = b(input int)

    # Test inputs are not negative
    bltz $s0, error     # branch on less than zero
    bltz $s1, error

    # Test 2nd input is a square
    mul $t0, $s0, $s0
    bne $t0, $s1, error

    # Print solution string prompt
    la   $a0, solu($0)
    addi $v0, $0, 4
    syscall


loopinit:
    addi  $s2, $0, 0      # i = 0
loop:
    slti  $t0, $s2, 5     # run for 5 loops
    beq   $t0, $0,  exit

    add $a0, $s0, $s2
    jal nextsquare

    add $a0, $v0, $0    # Load result of nextsquare to print
    li  $v0, 1          # Code for print int
    syscall
    li  $a0, 32         # Print space char
    li  $v0, 11         # Code for print string
    syscall

    addi $s2, $s2, 1    # i++
    j loop


error:
    la   $a0, errmsg
    addi $v0, $0, 4     # Print errmsg string
    syscall
    j exit              # Jump, just to be explicit

exit:
    la  $a0, endl       # Print newline
    li  $v0, 4          # Code for print string
    syscall
    lw $ra, 0($sp)      # Reload original return address
    addi $sp, $sp, 4    # Decrement stack pointer
    jr $ra


#---------------------------------------------------------------------------
# Next Square Function:
# (N+1)^2 = N^2 + 2xN + 1
#   = N^2 + N + (N + 1)
#
# args: $a0 --> N
# Consumes: a0
# Returns: v0
#---------------------------------------------------------------------------
nextsquare:
    mul  $v0, $a0, $a0  # v0 = N^2
    add  $t0, $a0, $a0  # 2xN
    add  $v0, $v0, $t0  # v0 += 2N
    addi $v0, $v0, 1    # v0 += 1
    jr $ra

