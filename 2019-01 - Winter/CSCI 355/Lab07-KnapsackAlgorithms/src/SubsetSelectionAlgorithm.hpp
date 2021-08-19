/* SubsetSelectionAlgorithm.hpp
 * ---------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 *
 * Purpose: provides an interface to algorithms solving "the Knapsack Problem".
 *          Program against this interface to have a guarantee that any one can
 *          be substituted for the other. Thank you Laura Liskov.
 *
 * 0-1 Knapsack problem:
 *      Given a set of n items, each with integer values and weights, find a
 *      subset of items with the maximum sum of their values with the condition
 *      that the sum of their weights is smaller than or equal to the integer
 *      capacity W of the knapsack.
 */
#ifndef SUBSETSELECTIONALGORITHM_HPP_INCLUDED
#define SUBSETSELECTIONALGORITHM_HPP_INCLUDED

#include <vector>
#include "loot.hpp"

class SubsetSelectionAlgorithm {
public:
    virtual ~SubsetSelectionAlgorithm() {}

    virtual auto most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
        -> std::vector<loot> = 0;
};

#endif // SUBSETSELECTIONALGORITHM_HPP_INCLUDED
