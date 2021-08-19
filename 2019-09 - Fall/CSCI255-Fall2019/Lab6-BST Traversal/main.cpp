/* main.cpp (originally TestBST.cpp)
 * ---------------------------------
 * CSCI 255
 * Lab 6:   BST Traversal
 * Authors: Darwin Jacob Groskleg
 * Purpose: to test TraversableBST's capacity to be used to implement a sorting
 *          algorithm of numbers.
 */
#include <iostream>
#include <array>
#include "traversable_bst.hpp"
using namespace std;

int main() {
// 1. In your main.cpp file, implement a sorting algorithm based on inorder
//    traversal of BST:
    // 1. Read n integers. 2. Create an empty BST.
    // 3. Insert the n integers into the BST by repeatedly using the insert
    //    method that you already implemented in the previous lab.
    TraversableBST<int> bst;
    cerr << "Integers to read: ";
    int n = 0;
    cin >> n;
    if (n > 0) {
        cerr << ">\t";
        int z;
        while (n--) {
            cin >> z;
            bst.insert(z);
        }
    } else {    // default case
        cout << "\nDefaulting to saved (unsorted) set of numbers: \n\t";
        array<int,10> arbit_z_10{{ 76, 28, 14, 64, 90, 79, 29, 33, 41, 77 }};
        for (auto v : arbit_z_10) {
            cout << v << ' ';
            bst.insert(v);
        }
    }
    // Depth-First Traversal Sorting
    // 4. Call the inorder method to do an inorder traversal of the BST and 
    //    print the n integers. The numbers will be printed in ascending sorted
    //    order.
    cout << "\nQ1. Sorted via Inorder Depth-First Traversal Algorithm:\n\t";
    bst.inorder();

// 2. Implement the breath-first traversal algorithm.
    cout << "\nQ2. Path of the Breath-First Traversal Algorithm:\n\t";
    bst.breadthFirst();

    cout << "\nCompared with Preorder Depth-First Traversal Path:\n\t";
    bst.preorder();

    return 0;
}
