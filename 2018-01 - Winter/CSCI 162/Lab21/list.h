/* Filename: list.h
 * --------------------
 * Author:  M. van Bommel & Darwin Jacob Groskleg
 * Date:    Thursday, March 22, 2018
 * Class:   CSCI 162
 * Lab:     #21
 *
 * Purpose: define (declare and implement) the classes for ListNode and List.
 * Because this is a template, the implementation is also defined in this
 * file.
 *
 * Changes: List#reverse() method was added.
 */
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include <cstdlib>

/* ListNode class, required to define the List class.
 */
template <class T>
class ListNode {
    public:
        T value;
        ListNode *next;

        ListNode(T val, ListNode *n = NULL) { value = val; next = n; }
};


template <class T>
class List {
    private:
        ListNode<T> *head, *tail;
        int size;
    public:
        List()                 { head = tail = NULL; size = 0; }
        bool insertAtFront(T);
        bool insertAtEnd(T);
        bool deleteFromFront();
         T   getFront() const;
        int  getSize()         { return size; }
        bool empty()           { return size == 0; }
        void display() const;
        void reverse();
};

template <class T>
bool List<T>::insertAtFront(T val) {
    ListNode<T> *temp = new ListNode<T>(val, head);
    if (temp == NULL) return false;
    head = temp;
    if (tail == NULL) tail = head;
    size++;
    return true;
}

template <class T>
bool List<T>::insertAtEnd(T val) {
    ListNode<T> *temp = new ListNode<T>(val, NULL);
    if (temp == NULL) return false;
    if (head == NULL) head = temp;
    else tail->next = temp;
    tail = temp;
    size++;
    return true;
}

template <class T>
bool List<T>::deleteFromFront() {
    ListNode<T> *temp = head;
    if (temp == NULL) return false;
    if (tail == head) head = tail = NULL;
    else head = head->next;
    delete temp;
    size--;
    return true;
}

template <class T>
T List<T>::getFront() const {
    if (head == NULL)
    {
        std::cout << "Cannot take front of empty list!\n";
        exit(EXIT_FAILURE);
    }
    return head->value;
}

template <class T>
void List<T>::display() const {
    ListNode<T> *temp = head;
    std::cout << "Head -> ";
    while (temp != NULL)
    {
        std::cout << temp->value << " -> ";
        temp = temp->next;
    }
    std::cout << "NULL\n";
}

/* Method Name: List#reverse()
 * Usage: mylist.reverse();
 * ------------------------
 * Implementation notes: uses 3 extra pointers to reverse the list,
 *  - previous
 *  - current
 *  - temp (to not be confused with next)
 *
 *  Does not check if there's enough memory to create ListNode pointers.
 *  Assumes tail->next points to null.
 */
template <class T>
void List<T>::reverse() {
    tail = head;
    ListNode<T> *previous;
    ListNode<T> *current  = head;

    if (size > 1) {
        ListNode<T> *temp = head->next;
        while (temp != NULL) {
            previous = current;
            current  = temp;
            temp     = temp->next;

            current->next = previous;
        }
    }

    head = current;
    if (size > 0) tail->next = NULL;
}

#endif // LIST_H_INCLUDED
