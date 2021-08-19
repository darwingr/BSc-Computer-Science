/* PrintableTree.hpp
 * ------------------
 * Authors: Darwin Jacob Groskleg
 * Course:  CSCI 255
 * Lab:     #9 - Heap
 * Date:    Tuesday, November 6, 2018
 *
 * Purpose: provides an approach to printing out tree-like data structures.
 *          Follows the command pattern.
 */
#ifndef PRINTABLE_TREE_HPP_INCLUDED
#define PRINTABLE_TREE_HPP_INCLUDED

#include <vector>
#include <sstream>
#include <cmath>

/// Binary Trees only
class PrintableTree {
    const int levels = 0;
    std::vector< std::vector<int>> tree_rows;

public:
    PrintableTree(int levels_ = 0):
        levels{levels_},
        tree_rows(levels)
    {
//        // Initialize each row
//        for (int i=1; i<=levels; i++) {
//
//        }
    }


    // TODO how to load the tree?
    bool add_row(int row_number, const std::vector<int>& new_row) {
        if (row_number < 1 || row_number > levels)  return false;
        int size = log2(row_number-1);
        if (size != (int) new_row.size())   return false;

        tree_rows.at(row_number) = new_row;
        return true;
    }

    auto send_stream() -> std::stringstream {
        std::stringstream output;
        if (levels == 0)    output << "EMPTY TREE\n";

        for (auto& row : tree_rows) {
            // TODO calculate how branches to the parent branch to draw
            // TODO calculate offset spaces from the left to start drawing row
            for (auto& node : row) {
                output << node << " ";
            }
            output << '\n';
        }

        return output;
    }
};

#endif // PRINTABLE_TREE_HPP_INCLUDED
