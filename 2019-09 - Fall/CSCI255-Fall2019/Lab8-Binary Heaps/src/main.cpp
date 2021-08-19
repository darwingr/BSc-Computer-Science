/* main.cpp
 * --------
 * Course:  CSCI 255
 * Lab:     # 8 Binary Heap
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: Tests the MakeHeap and Heapify functions by asking the user to input
 *          the integers of an arbitrary array, calling MakeHeap on the array
 *          and outputting the array.
 *
 *          This main function needed to be separated from the heap code in
 *          order to be able to call and test the heap code from multiple files.
 *
 * Console Sample:
 *      Input an arbitrary number of integers, put a right brace '}' when done:
 *      { 1 2 3 4 5 6 7 8 9 12 23 34 45 56 67 78 89 99 }
 *      Transformed into a binary max-heap:
 *      { 99, 89, 67, 78, 23, 45, 56, 8, 9, 12, 5, 34, 6, 3, 7, 2, 1, 4 }
 */
#include <iostream>
#include <vector>

#include "heap.hpp"

int main() {
    std::cout << "Input an arbitrary number of integers, "
              << "put a right brace ' }' when done:\n"
              << "{ ";

    std::vector<int> arbitrary_array;
    int number_in;  // Will loop until it does not give an int
    while (std::cin >> number_in)
        arbitrary_array.push_back(number_in);

    MakeHeap(arbitrary_array.data(), arbitrary_array.size());

    auto comma = [&arbitrary_array] (int element) {
        return (element == arbitrary_array.back()) ? " " : ",";
    };
    std::cout << "Transformed into a binary max-heap:\n{";
    for (int el : arbitrary_array)
        std::cout << ' ' << el << comma(el);
    std::cout << "}\n";

    return 0;
}
