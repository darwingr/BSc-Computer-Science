/* BinaryHeap.hpp
 * --------------
 * Course:  CSCI 255
 * Lab:     # 8 Binary Heap
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: Provide an interface for the heap code that is separate from main.
 *          This is an object oriented implentation of a max binary heap.
 *
 *          THIS IS NOT REQUIRED CODE BUT INCLUDED OUT OF INTEREST!
 */
#ifndef BINARYHEAP_HPP_INCLUDED
#define BINARYHEAP_HPP_INCLUDED

#include <algorithm>
#include <vector>

#include "PrintableTree.hpp"

//// Max Heap
class BinaryHeap {
    std::vector<int> heap_array;
    int              heap_size;

public:
    /// HeapSort
    /// Sort by removing elements from a heap until it is empty.
    ///
    /// Complexity:
    ///     T(n) = O(n log n) where n is the number of elements in the array.
    static auto heap_sort() -> std::vector<int>;

    /// MakeHeap
    /// XXX returns an owning pointer to a heapified array.
    ///
    /// Complexity:
    ///     T(n) = O(n) where n is the number of elements in the array.
    static BinaryHeap make_heap(int heap_array[], const int heap_size) {
        return BinaryHeap(heap_size, heap_array);
    }

    /// Ctor must be strictest to avoid undefined behaviour while other make
    /// functions may be more permissive and adaptive.
    ///
    /// Validate: ...use vector and defer handing these problems.
    ///     - heap_size_ is not larger than the array_size
    ///     - heap_array_ is not too big VS. array_size, which should throw
    ///       based on aggregate initialization rules.
    BinaryHeap(const int heap_size_, int heap_array_[]) :
        heap_array{ heap_size_ * 2, *heap_array_ },
        heap_size{ heap_size_ }
    {}

   ~BinaryHeap();

    /// Insert
    ///
    /// Complexity:
    ///     T(n) = O(lg n)
    void insert(int element) {
        if (heap_size == static_cast<int>(heap_array.size()))
            heap_array.push_back(element);
        else // heap_size is less
            heap_array.at(heap_size);
        heap_size++;
//        increase_key(i, key);
    }

    /// ExtractMax
    /// Removes the max value from the heap and returs it.
    /// The memory is not deallocated just ignored.
    ///
    /// Complexity:
    ///     T(n) = O(lg n)
    int extract_max() {
        int max{ heap_array.at(root) };

        heap_array.at(root) = heap_array.at(--heap_size);
        heapify(root);

        return max;
    }

    /// Using DFS will produce an object that can readily be used to represent
    /// the state of the heap visually as a tree.
    //
    /// Complexity:
    ///     T(n) = O(n)
    auto export_state() const -> PrintableTree {
        return PrintableTree(); // not included in project
    }

private:
    const int root = 0;

    /// XXX GUARD node is not negative
    int parent(int node_position) { return (node_position - 1) / 2; }
    int   left(int node_position) { return 2 * node_position + 1; }
    int  right(int node_position) { return 2 * node_position + 2; }

    /// IncreaseKey

    /// Heapify(node);
    void heapify(const int node);
};

#endif // BINARYHEAP_HPP_INCLUDED
