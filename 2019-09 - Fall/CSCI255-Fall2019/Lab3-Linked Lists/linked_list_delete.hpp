/* linked_list_delete.hpp
 * ----------------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, March 10, 2020
 *
 * Purpose:  implement method as part of assignment 2.
 */
#ifndef LINKED_LIST_DELETE_HPP_INCLUDED
#define LINKED_LIST_DELETE_HPP_INCLUDED

#include "linked_list.hpp"
#include <string>

class LinkedListD : public LinkedList {
  public:
    std::string print() const;
    void deleteIthNode(int i);
    void deletePos(LinkedList& list2);
    bool validEnds() const;
};
#endif // LINKED_LIST_DELETE_HPP_INCLUDED
