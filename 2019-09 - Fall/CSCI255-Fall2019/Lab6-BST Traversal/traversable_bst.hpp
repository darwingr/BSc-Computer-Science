/* traversable_bst.hpp
 * -------------------
 * CSCI 255
 * Lab 6:   BST Traversal
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: to extend the BST class from Lab #5 to be able to do breadth-first
 *          traversal operations.
 *
 * Open-Closed Principle: be open to extension, closed for modification.
 */
#ifndef TRAVERSABLE_BST_HPP_INCLUDED
#define TRAVERSABLE_BST_HPP_INCLUDED

#include "bst.hpp"

#include <initializer_list>
#include <queue>
#include <iostream>

template <typename T>
class TraversableBST : public BST<T> {
    using node = BSTNode<T>;
public:
    TraversableBST() = default; // required for inheriting class
    // Copy-Constructor is easy when you can traverse the copy
    TraversableBST(const TraversableBST& rhs) {
        auto ordered_values = rhs.breadthFirstCopy(rhs->root);
        for (auto &v :ordered_values)
            this->insert(v);
    }
    TraversableBST(std::initializer_list<T> inorder_list) {
        for (auto &n : inorder_list)
            this->insert(n);
    }

// Depth-First Traversal
    // Sorted Order
    void inorder(node* p);
    inline void inorder() { inorder(this->root); }

    // By-Row Starting from Root
    void preorder(node* p);
    inline void preorder() { preorder(this->root); }

// Breadth-First Traversal
    void breadthFirst(node* p);
    inline void breadthFirst() { breadthFirst(this->root); }

private:
    std::queue<T> breadthFirstCopy(node* p) const;
    inline void visit(node* p) { std::cout << p->key << ' '; }
};


/// IMPLEMENTATION

template<typename T>
void TraversableBST<T>::inorder(node* p) {
    if (p != nullptr) {
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}

template<typename T>
void TraversableBST<T>::preorder(node* p) {
    if (p != nullptr) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<typename T>
void TraversableBST<T>::breadthFirst(node* p) {
    for (auto values = breadthFirstCopy(p); !values.empty(); values.pop())
        std::cout << values.front() << ' ';
}

template<typename T>
std::queue<T> TraversableBST<T>::breadthFirstCopy(node* p) const {
    std::queue<node*> frontier;
    std::queue<T> pipe;

    if (p != nullptr) {
        frontier.push(p);
        while (!frontier.empty()) {
            p = frontier.front();
            frontier.pop();

            pipe.push(p->key);

            if (p->left != nullptr)
                frontier.push(p->left);
            if (p->right != nullptr)
                frontier.push(p->right);
        }
    }
    return pipe;
}

#endif // TRAVERSABLE_BST_HPP_INCLUDED
