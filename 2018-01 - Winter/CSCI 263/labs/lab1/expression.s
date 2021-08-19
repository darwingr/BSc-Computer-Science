# expression.s
# ------------
# Author: Darwin Jacob Groskleg
# Class: CSCI 163 - Lab #1
# Date:  17 January 2018
#
# Purpose:
# Evaluate the expression (10+9)-(8+7) and print the result.
# Equivalent C++ statement:  cout << (10 + 9)-(8+7) << endl;
# Result should be 4
#
# There are four parts to this program.
#   Evaluate the expression.
#   Print the result.
#   Print endl.
#   Return.
#
# Console:
# (spim) load "expression.s"
# (spim) run
# 4
#

.text
.globl main

main:
    # Evaluate the expression.
    # Put the final result in a0 to prepare for the syscall.
    li  $t0, 10     # Put 10 in a register
    li  $t1, 9      # Put 9 in a register
    li  $t2, 8      # Put 8 in a register
    li  $t3, 7      # Put 7 in a register
    add $a0, $t0, $t1   # a0 = t0 + t1
    add $a1, $t2, $t3   # a1 = t2 + t3
    sub $a0, $a0, $a1   # a0 = a0 - a1

    # Print the integer result in a0
    li  $v0, 1      # Load the system call number
    syscall

    # Print endl
    la  $a0, endl   # Load the address of the string
    li  $v0, 4      # Load the system call number
    syscall

    # Return
    li  $v0, 0      # Load return value in v0
    jr  $ra     # Return

.data

endl:   .ascii "\n"
