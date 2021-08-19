/* heap.cpp
 * --------
 * Course:  CSCI 255
 * Lab:     # 8 Binary Heap
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: To implement the MakeHeap and Heapify functions described in the
 *          lecture slides for a max-heap. Then test it by asking the user to
 *          input the integers of an arbitrary array, calling MakeHeap on the
 *          array and outputting the array.
 *
 * NOTICE: the procedural/imperative approach of passing c-arrays to MakeHeap is
 *         very unsafe. Use safer container types like std::array.
 */
#include "heap.hpp"

#include <algorithm>
#include <vector>

/// MakeHeap
///
/// Transforms a partially filled array of unordered integers into a binary
/// max-heap. Needs a given heapsize to determine by how full the array is.
///
/// Complexity:
///     T(n) = O(n)
///
void MakeHeap(int heap_array[], const int heapsize) {
    // Start with the parent of the last node then iterate to the first.
    int last_node = heapsize - 1;
    for (int i = parent_node(last_node); i>=0; i--)
        Heapify(heap_array, heapsize, i);
}


/// Heapify
///
/// Given a heap node that potentially violates the max-heap property,
/// down-rotate the node until the property is resolved.
///
/// Max-Heap Property:
///  0. The largest element is stored at the root.
///  1. For every node in the heap,
///      its value is greater or equal to that of its children.
///
/// Complexity:
///     T(n) = O(lg n) on a subtree of size n.
///
void Heapify(int heap_array[], const int heap_size, int node_position) {
    while (node_position < heap_size) {
        // Compute in one instruction with a binary shift (Cormen, p152).
        int left_i  = 2 * node_position + 1;
        int right_i = 2 * node_position + 2;
        int max_i = node_position;

        auto child_is_bigger = [heap_array, heap_size] (int child, int other) {
            return (child             < heap_size &&
                    heap_array[other] < std::max(heap_array[other],
                                                 heap_array[child]) );
        };

        if (child_is_bigger(left_i,  max_i))    max_i = left_i;
        if (child_is_bigger(right_i, max_i))    max_i = right_i;
        if (max_i == node_position)             break;

        std::swap(heap_array[node_position], heap_array[max_i]);
        node_position = max_i;
    }
}
