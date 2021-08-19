/* linked_list_delete.cpp
 * ----------------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, March 10, 2020
 *
 * Purpose:  implement method as part of assignment 2.
 */
#include "linked_list_delete.hpp"

#include <cassert>
#include <sstream>

namespace {
// Delete the first node from a chain of nodes,
// returning a pointer to the rest of the list.
Node* decapitate(Node* sublist_head) {
  if (sublist_head == nullptr) return nullptr;
  Node* neck = sublist_head->next;
  sublist_head->next = nullptr; // protect the body
  delete sublist_head;
  return neck;
}
}

// Valid End States
//  1 head points to first node OR nullptr if empty
//      - i's successor OR nullptr if none
//  2 tail points to last node  OR nullptr if empty
//      - i's precedant OR nullptr if none
//  3 i's precedant points to i's next node OR nullptr if none
//
// Boundary Conditions:
//  A i is out of range for node count (i > nodes-1),
//      then exit. DON'T KNOW UNTIL YOU REACH THE END!
//  B i'th element found,
//      then (fix head), fix precedant and delete.
//      Exit optional.
//  C End of list reached,
//      then fix tail pointer.
//
void LinkedListD::deleteIthNode(int i) {
    // GUARD: domain of i, a position is positive
    assert(i >= 0);
    if (i < 0)  return;

    Node** link_ptr = &head; // Traverse the links, not the nodes
    Node*  alt_tail = nullptr;
    // Linked List of n nodes has k=n+1 links
    for (int k=0;  *link_ptr != nullptr && k<=i;  k++) {

        if (k == i) { // Condition B, delete and fix precedent pointer
            if (*link_ptr == tail)  tail = alt_tail; // fix the tail
            *link_ptr = decapitate(*link_ptr);
        } else {
            alt_tail = *link_ptr;
            link_ptr = &(*link_ptr)->next;
        }
    }
}

bool LinkedListD::validEnds() const {
    if (head == nullptr) // isEmpty
        return tail == nullptr;
    else
        return tail != nullptr;
}

std::string LinkedListD::print() const {
    std::stringstream s;
    s << "HEAD";
    Node* nodeptr = head;
    //int tailpos = -1;
    while (nodeptr != nullptr) {
        s << "->(" << nodeptr->info;
        if (nodeptr == tail)
            s << " <-TAIL";
            //tailpos = s.tellp();
        s << ")";

        nodeptr = nodeptr->next;
    }
    //if (tailpos < 0)
    //    tailpos = s.tellp();
    //std::string gap(tailpos, ' ');
    s        << "->nullptr";
    //  << gap << "   ^TAIL\n";
    if (tail == nullptr) s << "<-TAIL\n";
    else s << "\n";
    return s.str();
}

