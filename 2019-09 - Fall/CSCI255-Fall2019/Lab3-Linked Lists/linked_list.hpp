/* linked_list.hpp
 * ---------------
 * Authors: Darwin Jacob Groskleg, Man Lin
 * Date:    Tuesday, September 24, 2019
 * CSCI 255
 * Lab 3: Linked Lists
 *
 * Purpose: declare the interface for a linked list of integers.
 */
#ifndef LINKED_LIST_HPP_INCLUDED
#define LINKED_LIST_HPP_INCLUDED

class Node {
  public:
    int info;
    Node *next;
    // O(1) - simple assignment
    Node(int el = 0, Node* n = nullptr) {
        info = el;
        next = n;
    }
    ~Node();
};

class LinkedList {
  public:
    // O(1) - simple assignment
    LinkedList() { head = tail = nullptr; }

    ~LinkedList();

    // O(1) - single comparison
    // Returns true if empty.
    bool isEmpty() const { return head == nullptr; }

    // Inserts a new node with the given value to the head of the list.
    void addToHead(int el);

    // Deletes the node at the tail of the list (if any) and returns
    // its value.
    int  deleteFromTail();

    // Determines if a particular value el (argument 1) is in this list and also
    // in another list (argument 2).
    // Returns TRUE if it is in the list, FALSE otherwise.
    bool isInBothList (int el, const LinkedList& another) const;

    // Checks whether the current linked list has the same contents of another.
    //
    // For example, if L1 and L2 are objects of type LinkedList, then
    // L1.same(L2) will return TRUE if L1 has the same contents as L2,
    // and FALSE otherwise.
    bool same(const LinkedList&) const;

  protected:
    Node *head;
    Node *tail;
    bool isInList(int el) const;
};

#endif // LINKED_LIST_HPP_INCLUDED
