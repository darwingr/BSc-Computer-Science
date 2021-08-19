/* heap.hpp
 * --------
 * Course:  CSCI 255
 * Lab:     # 8 Binary Heap
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: Interface to the c-style imperative/procedural implementations of
 *          MakeHeap and Heapify.
 */
#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

/// MakeHeap
///
/// Creates an integer max-heap from a given set of numbers.
///
///
void MakeHeap(int [], const int);


/// Heapify
///
/// Ensures the heap property holds for given node.
///
void Heapify(int [], const int , int);


/// parent_node
///
/// Given a node position in an array returns the position of its parent.
///
inline int parent_node(int node_position) {
    return node_position / 2;
}

#endif // HEAP_HPP_INCLUDED
