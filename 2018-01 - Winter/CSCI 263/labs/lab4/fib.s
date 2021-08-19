# fib.s
# ------
# Lab #4 - Recursive Functions in MIPS (Fibonacci)
#
# Author: Darwin Jacob Groskleg
# Class:  CSCI 263
# Date:   Saturday, April 7th, 2018
#
# Purpose:
# Learn to implement recursive functions and how to use stack pointers in
# assembly language. Prints the nth number in the fibonacci sequence.
#
# Console Sample:
# -----------------------------------------------------------------------------
# (spim) load "square.s"
# (spim) run
# Enter an integer (coefficient n): -1
#   INVALID INPUT: must be positive.
# (spim) run
# Enter an integer (coefficient n): 0
#   The Fibonacci number is: 0
# (spim) run
# Enter an integer (coefficient n): 1
#   The Fibonacci number is: 1
# (spim) run
# Enter an integer (coefficient n): 4
#   The Fibonacci number is: 3
# (spim) run
# Enter an integer (coefficient n): 10
#   The Fibonacci number is: 55
# -----------------------------------------------------------------------------

.data
prompt1: .asciiz "Enter an integer (coefficient n): "
results: .asciiz "  The Fibonacci number is: "
errmsg:  .asciiz "  INVALID INPUT: must be positive. "
endl:    .asciiz "\n"

.text
main:
    # accept input
    la   $a0, prompt1
    addi $v0, $0, 4     # Print prompt1 string
    syscall
    addi $v0, $0, 5     # Read integer
    syscall

    # Test N is not zero
    bltz $v0, error     # branch on less than zero

    move $a0, $v0       # a0 = n
    jal FIB
    add $s0, $v0, $0    # s0 = FIB(n)

    la   $a0, results   # print result prompt
    addi $v0, $0, 4     # Code for printing string
    syscall
    add  $a0, $s0, $0   # print result of FIB(n)
    addi $v0, $0, 1     # Code for printing int
    syscall

    j     exit

error:
    la   $a0, errmsg
    addi $v0, $0, 4     # Print errmsg string
    syscall
    j    exit           # Be explicit

exit:
    la   $a0, endl      # Print "endl" message
    addi $v0, $0, 4     # Code to print string
    syscall

    li    $v0, 10       # Code for exit
    syscall

#---------------------------------------------------------------------------
# Fibonacci Function:
# Returns the nth value of the fibonacci sequence starting from:
#   0 = 0,
#   1 = 1,
#   2 = 1,
#   3 = 2,
#   ...
#
# args: $a0 --> n
# Consumes: a0, s0, s1
# Returns: v0
#---------------------------------------------------------------------------
FIB:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $s0, 4($sp)
    sw   $s1, 0($sp)

    # Base Cases (n in {0, 1})
    add  $v0, $0,  $0       # v0 = 0
    beq  $a0, $0,  FIBEND   # n == 0
    addi $v0, $v0, 1        # v0 += 1
    beq  $a0, $v0, FIBEND   # n == 1

    # Recursive step
    move $s0, $a0
    addi $a0, $s0, -1
    jal  FIB                # FIB(n-1)
    move $s1, $v0
    addi $a0, $s0, -2
    jal  FIB                # FIB(n-2)
    add  $v0, $s1, $v0      # v0 = FIB(n-1) + FIB(n-2)

FIBEND:
    lw   $s1, 0($sp)
    lw   $s0, 4($sp)
    lw   $ra, 8($sp)
    addi $sp, $sp, 12
    jr   $ra                # Return

