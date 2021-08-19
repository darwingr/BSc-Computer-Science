# posrunopt.s
# -----------
# Date:   24 January 2018
# Student: Darwin Jacob Groskleg
# Student ID: 200903596
#
# Purpose: An assembly language version of the C++ program posrun.cpp
#   that has an optimized for loop to decrease the number of instructions
#   executed in each iteration of the loop.
#   - optimized 2 add lines to 1 shift line

.text
.globl     posrun

# Preconditions:
#   1st parameter (a0) address of the first element of the array
#   2nd parameter (a1) size of the array
# Postconditions:     
#   result (v0) length of the longest consecutive run of positive
#     numbers in the array

posrun: li  $t0, 0            # t0 is count, count = 0
        li  $v0, 0            # v0 is maxrun, maxrun = 0
        li  $t1, 0            # t1 is k, k = 0

for:    slt $t2, $t1, $a1     # (k < size) ?
        beq $t2, $0, endfor   # if not, branch to end of loop
        sll $t2, $t1, 2       # shift k left by 2 (t2 = k * 2^3)
        add $t3, $t2, $a0     # t3 = address of list[k] (add 2 address)
        lw  $t4, 0($t3)       # t4 = list[k]
        slt $t5, $0, $t4      # (0 < list[k]) ?
        beq $t5, $0, else1    # if not, branch to else

if1:    addi $t0, $t0, 1      # count++
        j endif1              # branch to end of if

else1:  li  $t0, 0            # count = 0

endif1: slt $t2, $v0, $t0     # (maxrun < count) ?
        beq $t2, $0, endif2   # if not, branch to end of if

if2:    addi $v0, $t0, 0      # maxrun = count

endif2: addi $t1, $t1, 1      # k++
        j for                 # back to top of loop

endfor: jr  $ra               # r
