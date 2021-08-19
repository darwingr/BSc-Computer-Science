/* BranchAndBoundSelector.hpp
 * --------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#ifndef BRANCHANDBOUNDSELECTOR_HPP_INCLUDED
#define BRANCHANDBOUNDSELECTOR_HPP_INCLUDED
#include <vector>

#include "SubsetSelectionAlgorithm.hpp"
#include "loot.hpp"

/// Branch And Bound Strategy
///
/// An improvement on the backtracking algorithm, still using a state space tree.
/// Does not:
///     1) limit the ways of traversing the tree
///     2) only used for optimization problems.
class BranchAndBoundSelector : public SubsetSelectionAlgorithm {
public:
    /// Wraps the textbook's C-style implementation of the algorithm with a
    /// C++ style interface.
    auto most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
        -> std::vector<loot>;

private:
    struct node { int level, profit, weight; };

    void knapsack(int n, const int p[], const int w[], int W, int& maxprofit);
    float bound(node u,
            const int n, const int p[], const int w[], const int W);
};

#endif // BRANCHANDBOUNDSELECTOR_HPP_INCLUDED
