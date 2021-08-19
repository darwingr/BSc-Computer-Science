/* test_bst.cpp
 * ------------
 * CSCI 255
 * Lab 5:   Recursion, BST
 * Authors: Darwin Jacob Groskleg, Man Lin
 * Date:    Tuesday, October 8, 2019
 *
 * Purpose: Test the probram and make sure that it works correctly.
 *
 * CONSOLE
 * -----------------------------------------------------------------------------
 * $ g++ -std=c++11 test_bst.cpp
 * $ ./a.out
 * found 10, as expected.
 * cannot find 3, as expected.
 * found 10, as expected.
 * The bst contains 7 nodes in total (expecting 7).
 * -----------------------------------------------------------------------------
 */
#include <iostream>
#include "bst.hpp"

using namespace std;

int main() {
    BST<int> bst;
    bst.insert(5);
    bst.insert(10);
    bst.insert(2);
    bst.insert(15);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);

    int toSearch;
    BSTNode<int> *result;

    // search 10 by iterative method
    toSearch = 10;
    result = bst.search(toSearch);
    if (result != nullptr)
        cout << "found " << result->key << ", as expected." << endl;
    else
        cout << "cannot find " << toSearch << endl;

    // search 3 by recursive method
    toSearch = 3;
    result = bst.rSearch(toSearch);
    if (result != nullptr)
        cout << "found " << result->key << endl;
    else
        cout << "cannot find " << toSearch << ", as expected." << endl;

    // search 10 by recursive method
    toSearch = 10;
    result = bst.rSearch(toSearch);
    if (result != nullptr)
        cout << "found " << result->key << ", as expected." << endl;
    else
        cout << "cannot find " << toSearch << endl;

    // total # of nodes in bst
    cout << "The bst contains " << bst.count() << " nodes in total"
         << " (expecting 7).\n";
}
