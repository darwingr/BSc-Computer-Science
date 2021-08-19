/* main.cpp
 * --------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, September 24, 2019
 * CSCI 255
 * Lab 3: Linked Lists
 *
 * QUESTION: What is the Big-O time complexity (in terms of the number of nodes
 *           that have to be traversed) for each of those methods?
 *
 * ANSWER:  time complexity is indicated in the definition comments for all
 *          methods, mostly "linked_list.cpp".
 *
 * PROGRAM OUTPUT:
 * -----------------------------------------------------------------------------
 * L1 isEmpty? true
 *
 * Added 1 to head of L1 and L2.
 * Added 2 to head of L1 and L2.
 * Added 3 to head of L1 and L2.
 * Added 4 to head of L1 and L2.
 * Added 5 to head of L1 and L2.
 * Added 6 to head of L1 and L2.
 * Added 7 to head of L1 and L2.
 * Added 8 to head of L1 and L2.
 * Added 9 to head of L1 and L2.
 * Added 10 to head of L1 and L2.
 *
 * L1 and L2 are the same? true
 *
 * Deleted 1 from the tail of L1.
 *
 * L1 and L2 are still the same? false
 *
 * Make L3, the reverse of L2
 * Element 2 is in both L2 & L3? true
 * Element 1 is in both L1 & L3? false
 * L2 = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
 * L3 = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
 * L1 = (10, 9, 8, 7, 6, 5, 4, 3, 2)
 * -----------------------------------------------------------------------------
 */
#include <iostream>
#include <iomanip>
#include <stack>

#include "linked_list.hpp"

using namespace std;

void printList(LinkedList &ll, string label);

int main() {
    LinkedList L1, L2;
    cout << "L1 isEmpty? " << boolalpha << L1.isEmpty() << "\n\n";

    for (int i=1; i<=10; i++) {
        L1.addToHead(i);
        L2.addToHead(i);
        cout << "Added " << i << " to head of L1 and L2.\n";
    }

    cout << "\nL1 and L2 are the same? " << boolalpha << L1.same(L2) << "\n\n";

    int n = L1.deleteFromTail();
    cout << "Deleted " << n << " from the tail of L1.\n\n";

    cout << "L1 and L2 are still the same? " << boolalpha << L1.same(L2)
        << "\n\n";

    cout << "Make L3, the reverse of L2\n";
    LinkedList L3;
    for (int i=10; i>=1; i--) L3.addToHead(i);

    cout << "Element 2 is in both L2 & L3? " << L2.isInBothList(2, L3) << '\n';
    cout << "Element 1 is in both L1 & L3? " << L1.isInBothList(1, L3) << '\n';

    printList(L2, "L2");
    printList(L3, "L3");
    printList(L1, "L1");

    return 0;
}

void printList(LinkedList &ll, string label="ll") {
    cout << label << " = (";
    stack<int> st;
    while (!ll.isEmpty())
        st.push(ll.deleteFromTail());
    if (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    while (!st.empty()) { cout << ", " << st.top(); st.pop(); }
    cout << ")\n";
}
