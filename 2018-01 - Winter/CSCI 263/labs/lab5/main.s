# main.s
# ------
# Lab #5 - Memory Allocation
#
# Author: Darwin Jacob Groskleg
# Class:  CSCI 263
# Date:   Saturday, April 7th, 2018
#
# Purpose: Build a linked list then delete every other node, displaying values # before and after.
# Implements assembly version of the C++ program in list.cpp .
# Calls functions in newdel.s and list.s .
#
# Console Sample:
# -----------------------------------------------------------------------------
# (spim) run
# 9 8 7 6 5 4 3 2 1 0
# 9 7 5 3 1
# -----------------------------------------------------------------------------

.text

.globl Node

# List node constructor.
# Preconditions:
#   1st parameter (a0) address of node
#   2nd parameter (a1) info
#   3rd parameter (a2) next

Node:
    sw   $a1, 0($a0)        # assign value to info field
    sw   $a2, 4($a0)        # assign value to next field
    jr   $ra                # return

.globl print

# Print a list.
# Preconditions:
#   1st parameter (a0) address of head node

print:
    addi $sp, $sp, -4       # make space on stack
    sw   $s0, 0($sp)        # preserve registers

    move $s0, $a0           # s0 = list

while1:
    beq  $s0, $zero, end1   # while list != NULL

    lw   $a0, 0($s0)        # list->info
    li   $v0, 1             # load the "print integer" syscall number
    syscall

    la   $a0, blank         # blank
    li   $v0, 4             # load the "print string" syscall number
    syscall

    lw   $s0, 4($s0)        # list = list->next
    j    while1

end1:
    la   $a0, endl          # endl
    li   $v0, 4             # load the "print string" syscall number
    syscall

    lw   $s0, 0($sp)        # restore registers
    addi $sp, $sp, 4        # restore stack pointer
    jr   $ra

.globl main

# Build a list, then delete every other node.
main:
    addi $sp, $sp, -12      # make space on stack
    sw   $s0, 0($sp)        # preserve registers
    sw   $s1, 4($sp)
    sw   $ra, 8($sp)        # preserve return address

    li   $s0, 0             # s0 = list = NULL

    # Build the list.
    li   $s1, 0             # s1 = k = 0

for2:
    slti $t0, $s1, 10       # k < 10 ?
    beq  $t0, $0, end2

    li   $a0, 8             # list = new Node(k, list)
    jal  _new
    move $a0, $v0
    move $a1, $s1
    move $a2, $s0
    move $s0, $v0
    jal  Node

    addi $s1, $s1, 1        # k++
    j    for2

end2:
    # Print the list.
    move  $a0, $s0          # parameter = head node
    jal   print

    # Delete every other node in the list.
    move  $a0, $s0          # parameter = head node
    jal   select

    # Print the list again.
    move  $a0, $s0          # parameter = head node
    jal   print

    lw   $s0, 0($sp)        # restore registers
    lw   $s1, 4($sp)
    lw   $ra, 8($sp)        # restore return address
    addi $sp, $sp, 12       # restore stack pointer
    li   $v0, 0             # return 0
    jr   $ra

.data

blank:  .asciiz " "
endl:   .asciiz "\n"
