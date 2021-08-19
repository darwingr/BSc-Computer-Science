/* linked_list.cpp
 * ---------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, September 24, 2019
 * CSCI 255
 * Lab 3: Linked Lists
 */
#include "linked_list.hpp"

// Node Destructor
//
//  O(n) - depending on number n nodes are in the tail
//
// NOTE: Will delete the node it points to, and so on.
Node::~Node() {
    if (next != nullptr)
        delete next;
}

// LinkedList Destructor
//
//  O(n) - each node must be deleted first
//
// Deletes all nodes starting from the head. Each node then deletes the next.
LinkedList::~LinkedList() {
    if (head != nullptr)
        delete head;
}

// Method: addToHead
//
//  O(1) - no traversal necessary, only/always touches one end.
//
// Mutates: head, first element in the list.
void LinkedList::addToHead(int el) {
    Node *new_element = new Node(el, head);
    if (isEmpty())
        tail = new_element;
    head = new_element;
}

// Method: deleteFromTail
//
//  O(n) - must travel up the list to reach the 2nd last node to be the tail.
//
// Mutates: tail, last node
// Note:    If empty, will return 0.
int LinkedList::deleteFromTail() {
    int value = 0;
    if (!isEmpty()) {
        value = tail->info;
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node *new_tail = head;
            while (new_tail->next != tail)
                new_tail = new_tail->next;
            new_tail->next = nullptr;
            delete tail;
            tail = new_tail;
        }
    }
    return value;
}

// Method: isInList
//
//  O(n) - Must travel down the list, touching at most all n nodes.
//
// Mutates: nothing
bool LinkedList::isInList(int el) const {
    Node *node = head;
    while (node != nullptr) {
        if (node->info == el)
            return true;
        node = node->next;
    }
    return false;
}

// Method: isInBothList
//
//  O(n + m) - Linear, has to travel down both lists from the head to find a
//             match.
//
// Mutates: nothing
bool LinkedList::isInBothList(int el, const LinkedList& another) const {
    return isInList(el) && another.isInList(el);
}

// Method: same
//
//  O(n + m) - Linear, has to travel down both lists from the head, comparing
//             the node values at each point.
//
// Mutates: nothing
bool LinkedList::same(const LinkedList& another) const {
    Node *current = head;
    Node *other   = another.head;

    while (current != nullptr && other != nullptr) {
        if (current->info != other->info)
            return false;
        current = current->next;
        other   = other->next;
    }
    // if different sizes then 1 is not null and they won't have same contents
    if (current != nullptr || other != nullptr)
        return false;
    return true;
}
