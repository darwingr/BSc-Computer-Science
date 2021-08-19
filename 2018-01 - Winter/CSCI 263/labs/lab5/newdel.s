# newdel.s
# --------
# Purpose:
# Provides simplified versions of new and delete for allocating and
# deallocating memory. The function _new allocates space for new nodes in the
# linked list. The function _delete is deallocates memory and returns it to
# available memory on the heap.

.text

.globl _new

# Allocate a new block of memory.
# Preconditions:
#   1st parameter ($a0) number of bytes to be allocated
# Postconditions:
#   result ($v0) pointer to a block of memory
_new:
    li  $v0, 9      # load sbrk syscall number
    syscall         # Allocates memory from heap
    jr  $ra         # returns address of allocated memory


.globl _delete

# De-allocate a block of memory.
# (This implementation clears memory but does not return it to the heap.)
# Preconditions:
#   1st parameter ($a0) pointer to a block of memory
#   2st parameter ($a1) number of bytes to be de-allocated
# Postconditions:
#   result ($v0) pointer to a block of memory
_delete:
    add  $t0, $a0, $a1      # loop limit  = address + count
    li   $t1, 0xff          # fill pattern
    j    end3               # test at end of loop
while3:
    sb   $t1, 0($a0)        # fill memory with pattern
    addi $a0, $a0, 1        # increment address
end3:
    bne  $a0, $t0, while3
    jr   $ra                # return
