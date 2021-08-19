/* Thief.hpp
 * ---------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#ifndef THIEF_HPP_INCLUDED
#define THIEF_HPP_INCLUDED

#include "SubsetSelectionAlgorithm.hpp"
#include "loot.hpp"

class Thief {
    const int _knapsack_weight_limit;
    SubsetSelectionAlgorithm* strategy;
public:
    Thief(int knapsack_weight=0);

    auto fill_knapsack(std::vector<loot> takeable_items)
        -> std::vector<loot>;

    void set_strategy(SubsetSelectionAlgorithm * strat);
};
#endif // THIEF_HPP_INCLUDED
