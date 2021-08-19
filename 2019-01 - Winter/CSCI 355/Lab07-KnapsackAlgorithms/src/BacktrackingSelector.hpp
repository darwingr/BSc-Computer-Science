/* BacktrackingSelector.hpp
 * ------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#ifndef BACKTRACKINGSELECTOR_HPP_INCLUDED
#define BACKTRACKINGSELECTOR_HPP_INCLUDED
#include <vector>
#include "SubsetSelectionAlgorithm.hpp"
#include "loot.hpp"

/// Depth-first search with Backtracking
/// (pruning a depth-first exhaustive search)
class BacktrackingSelector : public SubsetSelectionAlgorithm {
public:
    /// Wraps the textbook's C-style implementation of the algorithm with a
    /// C++ style interface.
    auto most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
        -> std::vector<loot>;

private:
    void knapsack(size_t i, int profit, int weight);
    // Error in textbook missed last 2 arguments
    bool promising(size_t i, int profit, int weight);

    // Globally defined variables from the textbook

    // number of items given
    size_t n;

    // w and p, each indexed from 1 to n, containing positive integers sorted in
    // nonincreasing order according to the values of p[i]/w[i].
    std::vector<int>    w;     // loot weights
    std::vector<int>    p;     // loot prices

    double W;       // maximum possible weight
    int maxprofit;  // maximum profit so far

    // arrays[1 to n] where item is true if included
    std::vector<bool>   include; // set currently being tried
    std::vector<bool>   bestset; // most optimal set so far

    size_t numbest;     // number of items in the best set so far
    int profit;         // profit calculated in current track (potential max)
};

#endif // BACKTRACKINGSELECTOR_HPP_INCLUDED
