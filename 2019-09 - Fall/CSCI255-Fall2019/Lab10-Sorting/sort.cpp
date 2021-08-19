/* sort.cpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, November 21, 2019
 */
#include "sort.hpp"
#include <iostream>

SortingDetails merge(int A[], int left, int middle, int right);

// MergeSort recursive function
//  Move: consists of a single value relocation within the array A,
//        not copies into some dynamic array used to compute the correct move.
//  Comparison: consists of a comparison between 2 values within the array A for
//              the purpose of deciding whether a move is required,
//              not comparison of array indices used for bounds checking.
//
// Stable sorting
// T(n) = O( n log(n) )
// S(n) = O(n)
SortingDetails MergeSort(int A[], int left, int right)
{
    auto d = SortingDetails{};
    // Want to immediately return if range is not 2 elements or more.
    if (left >= right)
        return d;

    int middle = (left + right)/2;

    auto dl = MergeSort(A, left, middle);
    auto dr = MergeSort(A, middle+1, right);
    auto dm = merge(A, left, middle, right);
    d += dl + dr + dm;
    return d;
}

// Merges two sorted subarrays into a larger sorted array
// T(n) = O(n)
// S(n) = O(n)
SortingDetails merge(int A[], int left, int middle, int right)
{
    SortingDetails d{};
    int i1 = left;
    int i2 = middle + 1;

    int k  = 0; // sorted frontier index
    int *sorted = new int [right - left + 1];

    // Tracks moved if not into same relative position in the sorted array
    // then store it in the sorted array.
    auto compute_move = [&d, &sorted, &A, left] (int& dst, int& src) {
        if (dst != src-left)
            d.moves++;
        sorted[dst++] = A[src++];
    };

    // Initializing "sorted" array
    //  out of values to copy when i1 reaches the middle or i2 reaches end.
    while ((i1 <= middle) && (i2 <= right)) { // not comparison
        d.comparisons++;
        if(A[i1] < A[i2])
            compute_move(k, i1);
        else
            compute_move(k, i2);
    }

    // load the rest of the remaining elements,
    //      if the range has uneven number of elements
    while (i1 <= middle)
        compute_move(k, i1);
    while(i2 <= right)
        compute_move(k, i2);

    // Copy them back to the original array, overwriting it
    for (int i = left; i <= right; i++)
        A[i] = sorted[i-left];

    delete [] sorted;
    return d;
}

// Not Stable
// T(n) = O(n^2)
//      But on average T(n) = O(n lg(n))
// S(n) = O(1)
SortingDetails QuickSort(int A[], int start, int end) {
    SortingDetails d{};
    // Early Exit: degenate cases
    if (start >= end)
        return d;

    int left = start, right = end;
    int pivot = A[start];

    // Partition
    while (left < right) {
        while (A[right] >= pivot && left < right)
            d.comparisons++ && right--;
        d.comparisons++;
        if (left < right) {
            A[left] = A[right];
            d.moves++;
            left ++;
        }

        while (A[left] <= pivot && left < right)
            d.comparisons++ && left++;
        d.comparisons++;
        if (left < right) {
            A[right] = A[left];
            d.moves++;
            right --;
        }
    }
    A[left] = pivot;
    d.moves++;

    // Recursion
    if (start < left)
        d += QuickSort(A, start, left-1);
    if (left < end)
        d += QuickSort(A, left+1, end);

    return d;
}

// T(n) = O(n^2)
//      two nested loops
// S(n) = O(1)
//      no new allocations need to be made in relation to n
//      in place
// Is stable
// Is adaptive: efficient for mostly ordered sets -> O(n)
//
// The "playing-card" sorting algorithm
SortingDetails InsertionSort(int A[], int start, int end) {
    SortingDetails d{};
    int key, j;

    // Use i,j to search throught the unsorted portion of the array,
    //  elements to the right.
    for (int i=start+1; i<=end; i++) {
        key = A[i];
        j = i - 1;
        while (j >= start && A[j] > key) {
            d.comparisons++;
            A[j+1] = A[j];
            d.moves++;
            j--;
        }
        d.comparisons++;

        A[j+1] = key;
        d.moves++;
    }
    return d;
}

// T(n) = O(n^2)
//      two nested loops over n elements
// S(n) = O(1)
//      no new allocations need to be made in relation to n
SortingDetails SelectionSort(int A[], int start, int end) {
    SortingDetails d{};
    // Early Exit: degenate cases
    if (start >= end)
        return d;

    int min_index, j;
    for (int i=start; i<=end; i++) {
        min_index = i;
        j = i + 1;
        while (j <= end) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
            d.comparisons++;
            j++;
        }
        std::swap(A[min_index], A[i]);
        // swaps count as 2 moves, does 1 more swap than is necessary
        d.moves += 2;
    }
    return d;
}

// Helpers! ====================================================================

void displayArray(int A[], int size) {
    displayArray(A, 0, size-1);
}

void displayArray(int A[], int start, int end) {
    std::clog << "{";
    for(int i=start; i<=end; i++)
        std::clog << A[i] << " ";
    std::clog << "}\n";
}

// T(n) = O(n log(n))
void reverseSort(int A[], int start, int end) {
    MergeSort(A, start, end);
    while (start < end) {
        std::swap(A[start], A[end]);
        start++;
        end--;
    }
}

SortingDetails& SortingDetails::operator+(const SortingDetails& rhs) {
    this->comparisons += rhs.comparisons;
    this->moves       += rhs.moves;
    return *this;
}

SortingDetails& SortingDetails::operator+=(const SortingDetails& rhs) {
    this->comparisons += rhs.comparisons;
    this->moves       += rhs.moves;
    return *this;
}
