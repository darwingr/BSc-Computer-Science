/* huffman_tree.cpp
 * ----------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, November 26, 2019
 */
#include "huffman_tree.hpp"

#include <iostream>   // clog
#include <string>     // to_string
#include <utility>    // std::move
#include <algorithm>  // for move a range?

#include <cassert>

////////////////////////////////////////////////////////////////////////////////
// Tree Node Implementation
////////////////////////////////////////////////////////////////////////////////
HuffmanTree::HFNode::HFNode() :
    ch(0),
    freq(0),
    left(nullptr),
    right(nullptr)
{}

HuffmanTree::HFNode::HFNode(char c, double fr) :
    ch(c),
    freq(fr),
    left(nullptr),
    right(nullptr)
{}

HuffmanTree::HFNode::HFNode(char c, double fr, HFNode* l, HFNode* r):
    ch(c),
    freq(fr),
    left(l),
    right(r)
{}

// copy constructor
//HuffmanTree::HFNode::HFNode(const HFNode &obj) {
//}

std::string HuffmanTree::HFNode::huffman_code(std::string prefix) const {
    std::string hcode = "";
    // build the prefix code in the leaf
    if (ch != 0) // is leaf! Prefix is complete!
        return prefix+'.';
    if (left)
        hcode.append(left->huffman_code(prefix + '0'));
    if (right)
        hcode.append(right->huffman_code(prefix + '1'));

    return hcode;
}

bool HuffmanTree::HFNode::operator < (const HFNode& rhs) const {
    return this->frequency() < rhs.frequency();
}


////////////////////////////////////////////////////////////////////////////////
// HuffmanTree Implementation
////////////////////////////////////////////////////////////////////////////////
void HuffmanTree::add(char c, double frequency) {
    node_list.push_back({c, frequency});
}

// Uses a depth-first traversal?
std::string HuffmanTree::huffman_code() const {
    const HFNode *np = &node_list.front();
    std::string code = np->huffman_code("");
    code.erase(code.end()-1);   // remove last .
    return code;
}

// Repeat until only 1 node on list:
// - sort list of tree nodes by freqency
// - remove the first two tree nodes
// - create a new node with these trees as subtrees.
//      - frequency is sum of their frequencies.
//      - first extracted is on the left
// - Add the new node to the list.
//
// Prints debug data to stderr.
//
void HuffmanTree::make_decode_tree(void) {
    node_list.sort();
    assert(std::is_sorted(node_list.begin(), node_list.end()));

    std::clog << "Sorted char freqs: ";
    for (auto& n : node_list)
        std::clog << n.frequency() << '(' << n.symbol() << "), ";
    std::clog << '\n';

    while (node_list.size() > 1) {
        // Use a move constructor to avoid having multiple smart pointers to
        // the same child node
        HFNode *cf1 = new HFNode( std::move(node_list.front()) );
        // popped item will have destructor called only once it goes out of
        // scope, thus can be pointed to.
        node_list.pop_front();

        HFNode *cf2 = new HFNode( std::move(node_list.front()) );
        node_list.pop_front();

        auto freq_sum = cf1->frequency() + cf2->frequency();
        HFNode cf3{0, freq_sum, cf1, cf2};
        // push to front, gives precedence in sorting over others of same
        // frequency...assuming you have a stable-sorting algorithm.
        node_list.push_front(std::move(cf3)); //move!
        node_list.sort();
    }
}

// assumes `make_decode_tree` was run first
//
// given a binary string: "101...",
// assumes code is valid message for tree
//  - is only 1 or 0
//  - is only valid prefix codes
//
std::string HuffmanTree::decode_message(std::string code) const {
    std::string message = "";
    const HFNode *np = &node_list.front();
    while(!code.empty()) {
        if (code.front() == '0')
            np = np->leftp();
        else
            np = np->rightp();

        if (np->symbol() != 0) {
            message.push_back(np->symbol());
            np = &node_list.front();
        }
        code.erase(0); // pop_front
    }
    return message;
}

std::string HuffmanTree::to_dot() const {
    std::string dot = "digraph G {\n"
                      "    edge [label=0]\n"
                      "    graph [ranksep=0];\n"
                      "    node [shape=record];\n";
    const HFNode *np = &node_list.front();
    std::list<const HFNode *> q; // queue
    q.push_back(np);
    auto to_qstring = [] (double r) {
        return "" + std::to_string(r) + "";
    };
    while (q.size() > 0) {
        np = q.front();
        if (np->symbol() != 0) {// leaf
            dot.append("    ");
            dot.push_back(np->symbol());
            dot.append(" [label=\"{");
            dot.push_back(np->symbol());
            dot.append("|"+to_qstring(np->frequency())+"}\"];\n");
        }

        if (np->leftp()) {
            q.push_back(np->leftp());

            dot.append("    ");
            dot.append(to_qstring(np->frequency())+" -> ");
            if (np->leftp()->symbol() != 0) // child is a leaf
                dot.push_back(np->leftp()->symbol());
            else
                dot.append( to_qstring(np->leftp()->frequency()) );
            dot.append(";\n");
        }

        if (np->rightp()) {
            q.push_back(np->rightp());

            dot.append("    ");
            dot.append(to_qstring(np->frequency())+" -> ");
            if (np->rightp()->symbol() != 0) // child is a leaf
                dot.push_back(np->rightp()->symbol());
            else
                dot.append( to_qstring(np->rightp()->frequency()) );
            dot.append(" [label=1];\n");
        }

        q.pop_front();
    }
    dot.append("}");
    return dot;
}
