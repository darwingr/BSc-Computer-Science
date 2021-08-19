# list.s
# ------
# Lab #5 - Memory Allocation
#
# Author: Darwin Jacob Groskleg
# Class:  CSCI 263
# Date:   Saturday, April 7th, 2018
#
# Purpose:
# Delete every other node in a list.
# Calls functions in newdel.s .
#
# Console Sample:
# -----------------------------------------------------------------------------
# (spim) run
# 9 8 7 6 5 4 3 2 1 0
# 9 7 5 3 1
# -----------------------------------------------------------------------------

.text
.globl select

# Function Name: select     (aka selective delete)
#
# Precondtions:
#   1st parameter (a0) address of head node
# Postconditions:
#   Every other node is removed from the list and deleted.
select:
    addi $sp, $sp, -8       # make space on stack
    sw   $s0, 0($sp)        # preserve registers used by this function
    sw   $ra, 4($sp)        # preserve return address

    move $s0, $a0           # s0 = p = list

while:
    beq  $s0, $0, return    # while (p != NULL)
    lw   $t0, 4($s0)        # t0 = p->next
    beq  $t0, $0, endif     # if (p->next != NULL)
    lw   $t1, 4($t0)        # t1  = p->next->next
    sw   $t1, 4($s0)        # p->next = p->next->next

    move $a0, $t0           # 1st parameter = (the old) p->next
    addi $a1, $0, 8         # 2nd parameter = size of node (node is 8 bytes)
    jal _delete             # delete node

endif:
    lw   $s0, 4($s0)        # p = p->next
    j    while              # jump to beginning of loop

return:
    lw   $s0, 0($sp)        # restore registers used by this function
    lw   $ra, 4($sp)        # restore return address
    addi $sp, $sp, 8        # restore stack pointer
    jr   $ra                # return
