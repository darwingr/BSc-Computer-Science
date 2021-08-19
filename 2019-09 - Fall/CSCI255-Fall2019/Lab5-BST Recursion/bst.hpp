/* bst.hpp
 * -------
 * CSCI 255
 * Lab 5:   Recursion, BST
 * Authors: Darwin Jacob Groskleg, Man Lin
 * Date:    Tuesday, October 8, 2019
 */
#ifndef BST_HPP_INCLUDED
#define BST_HPP_INCLUDED

#if __cplusplus >= 202002L // if c++20
concept LessThanComparable<typename T> {
    bool operator < (const T& lhs, const T& rhs);
}
#endif

// BSTNode class: representing A Node in a Binary Tree
template<class T>
class BSTNode {
public:
    T key;
    BSTNode<T> *left, *right;

    BSTNode() {
        left = right = nullptr;
    }
    BSTNode(const T& el, BSTNode *l = nullptr, BSTNode *r = nullptr) {
        key = el; left = l; right = r;
    }
};

// BST class: Binary Search Tree
//      DJ Groskleg (modified)
template<class T>
    #if __cplusplus >= 202002L // if c++20
        requires LessThanComparable<T>
    #endif
class BST {
    using node = BSTNode<T>;
public:
    BST();

    void insert(const T & el); //insert el to the BST

    //iterative implementation of search
    auto search(const T & el) -> node*;
    //recursive search
    auto rSearch(const T & el) -> node*;

    int count(); //count the number of nodes in the BST

protected:
    node *root;

private:
    //recursive search helper method: starting from cur BSTNode
    auto recursiveSearch(node *cur, const T & el) -> node*;

    //helper method: count recursively from BSTNode r
    int recursiveCount(node *r);
};


// DJ Groskleg (added)
template <class T>
int BST<T>::recursiveCount(node *r) {
    if (r == nullptr)   return 0;
    return recursiveCount(r->left) + 1 + recursiveCount(r->right);
}

// DJ Groskleg (added)
template <class T>
int BST<T>::count() {
    return recursiveCount(root);
}

// DJ Groskleg (added)
template <class T>
auto BST<T>::rSearch(const T &el) -> node* {
    return recursiveSearch(root, el);
}

// DJ Groskleg (added)
template <class T>
auto BST<T>::recursiveSearch(node *cur, const T &el) -> node* {
    if (cur == nullptr)                           return nullptr;
    if (cur->key == el)                           return cur;

    node* left = recursiveSearch(cur->left, el);
    if (left  != nullptr && left->key  == el)     return left;

    node* right = recursiveSearch(cur->right, el);
    if (right != nullptr && right->key == el)     return right;

    return nullptr;
}

// M.Lin (pre-existing)
template <class T>
BST<T>::BST() {
    root = nullptr;
}

// Insert el to the BST
// M.Lin (pre-existing)
template <class T>
void BST<T>::insert(const T &el) {
    node  *p=nullptr, *prev=nullptr;
    p = root;
    while (p != nullptr){
        prev = p;
        if(p -> key > el)
            p = p-> left;
        else
            p = p->right;
    }
    if (root == nullptr)
        root = new node(el);
    else {
        if (el > prev->key)
            prev->right = new node(el);
        else
            prev->left  = new node(el);
    }
}

// M.Lin (pre-existing)
template <class T>
auto BST<T>::search(const T & el) -> node* {
    node * p = root;
    while (p != 0){
        if (p->key == el)
            return p;
        else{
            if(p-> key < el)
                p = p-> right;
            else
                p = p->left;
        }
    }
    return 0;
}

#endif // BST_HPP_INCLUDED
