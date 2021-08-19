/* BacktrackingSelector.cpp
 * ------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#include "BacktrackingSelector.hpp"
#include <algorithm>

auto BacktrackingSelector::
most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
    -> std::vector<loot>
{
    n = lootable_items.size();
    // Sort items by dollar per weight-unit in DECREASING order
    std::sort(lootable_items.rbegin(), lootable_items.rend());
    w = std::vector<int>(n);     // loot weights
    p = std::vector<int>(n);     // loot prices
    std::for_each(lootable_items.begin(), lootable_items.end(), [&](loot item) {
            w.push_back(item.weight);
            p.push_back(item.value); });

    W = weight_limit;
    maxprofit = 0;
    include = std::vector<bool>(false, n);
    bestset = std::vector<bool>(false, n);
    numbest = 0;

    knapsack(0, 0, 0);

    // Build the optimal list
    std::vector<loot> selection(numbest);
    auto is_in_bestset = [&] (loot l) {
        // Is bestset binary seachable? yes
        return std::binary_search(bestset.begin(), bestset.end(), l);
    };
    // O(n^2) or O(n log n) if bestset is sorted
    std::copy_if(lootable_items.begin(), lootable_items.end(),
            selection.begin(), is_in_bestset);

    return lootable_items;
}

/// Knapsack
///
/// From "Foundation of Algorithms 5ed, page 316.
void BacktrackingSelector::
knapsack(size_t i, int profit, int weight) {
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
        numbest = i;        // number of items considered
        bestset = include;  // this solution
    }

    if (promising(i, profit, weight)) {
        include[i+1] = true;    // include w[i+i]
        knapsack(i+1, profit + p[i+1], weight + w[i+1]);
        include[i+1] = false;
        knapsack(i+1, profit, weight);
    }
}

/// Promising
///
/// Checks if
///     - there is capacity left in the knapsack
///     - 
///
/// From "Foundation of Algorithms 5ed, page 316.
/// Textbook Error: left out 2 function arguments.
bool BacktrackingSelector::
promising(size_t i, int profit, int weight) {
    size_t j, k;
    int totweight;
    float bound;

    // weight is sum of weights of items included so far
    if (weight >= W)
        return false;
    else {
        j = i + 1;
        bound = profit;
        totweight = weight;
        while (j <= n && totweight + w[j] <= W) {
            totweight = totweight + w[j];
            bound = bound + p[j];
            j++;
        }
        k = j;
        if (k <= n)
            bound = bound + (W - totweight) * p[k]/w[k];

        return bound > maxprofit;
    }
}
