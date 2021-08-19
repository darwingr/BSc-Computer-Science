/* Filename: mylist.cpp
 * --------------------
 * Author:  M. van Bommel & Darwin Jacob Groskleg
 * Date:    Thursday, March 22, 2018
 * Class:   CSCI 162
 * Lab:     #21
 *
 * Purpose: to add a method to the template for a list class that reverses the
 * elements in a list according to a the given specification.
 * Shows the user the output of 7 specific operations as a demonstration.
 *
 * Console Output Sample:
 * -----------------------------------------------------------------------------
 * 1. Creates an empty list and displays it.
 * Head -> NULL
 *
 * 2. Reverse the empty list and displays it.
 * Head -> NULL
 *
 * 3. Adds a single node to the list and displays it.
 * Head -> 0 -> NULL
 *
 * 4. Reverses the single node list and displays it.
 * Head -> 0 -> NULL
 *
 * 5. Adds several more nodes to the list and displays it.
 * Head -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> NULL
 *
 * 6. Reverses the larger list and displays it.
 * Head -> 7 -> 6 -> 5 -> 4 -> 3 -> 2 -> 1 -> 0 -> NULL
 *
 * 7. Reverses the reversed list again and displays it.
 * Head -> 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> NULL
 * -----------------------------------------------------------------------------
 */
#include "list.h"
#include <iostream>

int main() {
    std::cout << "1. Creates an empty list and displays it.\n";
    List<int> myList;
    myList.display();

    std::cout << "\n2. Reverse the empty list and displays it.\n";
    myList.reverse();
    myList.display();

    std::cout << "\n3. Adds a single node to the list and displays it.\n";
    myList.insertAtEnd(0);
    myList.display();

    std::cout << "\n4. Reverses the single node list and displays it.\n";
    myList.reverse();
    myList.display();

    std::cout << "\n5. Adds several more nodes to the list and displays it.\n";
    for (int i=1; i<8; i++) { myList.insertAtEnd(i); }
    myList.display();

    std::cout << "\n6. Reverses the larger list and displays it.\n";
    myList.reverse();
    myList.display();

    std::cout << "\n7. Reverses the reversed list again and displays it.\n";
    myList.reverse();
    myList.display();

    return 0;
}
