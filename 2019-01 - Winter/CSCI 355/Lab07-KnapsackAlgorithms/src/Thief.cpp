/* Thief.cpp
 * ---------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#include "Thief.hpp"

// hide this from the outside
namespace {
class FillingStrategyDummy : public SubsetSelectionAlgorithm {
    inline auto most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
        -> std::vector<loot>
    {
        (void) weight_limit;    // silence compiler warning
        (void) lootable_items;  // for unused variables
        return {};
    }
};
}; // anon

Thief::Thief(int knapsack_weight) :
    _knapsack_weight_limit(knapsack_weight),
    strategy{new FillingStrategyDummy}
{
    if (_knapsack_weight_limit < 0)
        throw "Impossible knapsack weight limit";
}

auto Thief::fill_knapsack(std::vector<loot> takeable_items)
    -> std::vector<loot>
{
    return strategy->most_valuable_subset(_knapsack_weight_limit, takeable_items);
}

void Thief::set_strategy(SubsetSelectionAlgorithm * strat) {
    strategy = strat;
}
