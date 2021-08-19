/* sort.hpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Thursday, November 21, 2019
 */
#ifndef SORT_HPP_INCLUDED
#define SORT_HPP_INCLUDED

// Sort functions must be able to return sorting algorithm details.
//  - number of value comparisons
//  - number of data movement (values reorder, ie swap)
struct SortingDetails {
    int comparisons = 0;
    int moves       = 0;
    SortingDetails& operator+(const SortingDetails& rhs);
    SortingDetails& operator+=(const SortingDetails& rhs);
};

//void InsertionSort(int [], int, int, SortingDetails = SortingDetails{});
SortingDetails InsertionSort(int A[], int left, int right);
SortingDetails SelectionSort(int A[], int left, int right);
SortingDetails QuickSort(int A[], int start, int end);
SortingDetails MergeSort(int A[], int left, int right);

// Helpers
void displayArray(int [], int size);
void displayArray(int array[], int start, int end);

void reverseSort(int [], int start, int end);

#endif // SORT_HPP_INCLUDED
