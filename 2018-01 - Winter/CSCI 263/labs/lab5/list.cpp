#include <iostream>

using namespace std;

/* A node in a linked list. */
struct Node {
    int info;
    Node * next;

    Node(int i, Node * n) {
       info = i;
       next = n;
    }
};


/* Print a list. */
void print(Node * list) {
    while(list != NULL) {
       cout << list->info << " ";
       list = list->next;
    }
    cout << endl;
}


/* Delete every other node from a list.
 * Should be named: deleteEveryOther
 * but select is the expected name.
 */
void select(Node * list) {
    while(list != NULL) {
       if (list->next != NULL) {
           Node * p = list->next;
           list->next = list->next->next;
           delete p;
       }
       list = list->next;
    }
}


/* Build a list, then remove half the nodes. */
int main() {
    Node * list = NULL;   // Pointer to head node.

    // Build the list.
    for(int k = 0; k < 10; k++) {
       list = new Node(k, list);
    }

    // Print the list.
    print(list);

    // Delete every other node.
    select(list);

    // Print the list again.
    print(list);

    return 0;
}
