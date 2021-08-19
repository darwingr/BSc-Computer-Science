/* BranchAndBoundSelector.cpp
 * --------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#include "BranchAndBoundSelector.hpp"
#include <queue>

std::vector<loot> BranchAndBoundSelector::
most_valuable_subset(int weight_limit, std::vector<loot> lootable_items) {

}

/// Knapsack3
///
/// Taken from page 331 for Foundations of Algorithms 5ed
void BranchAndBoundSelector::
knapsack(int n,
         const int p[], const int w[],
         int W,
         int& maxprofit)
{
    // closure for clarity
    auto bound = [this,n,p,w,W](node u) { return this->bound(u, n, p, w, W); };

    std::queue<node> Q;
    node u, v{0,0,0}; // v is the root

    maxprofit = 0;
    Q.push(v);
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        u.level = v.level + 1;
        u.weight = v.weight + w[u.level];
        u.profit = v.profit + p[u.level];

        if (u.weight <= W && u.profit > maxprofit)
            maxprofit = u.profit;
        if (bound(u) > maxprofit)
            Q.push(u);

        // Set u to the child that does not include the next item
        u.weight = v.weight;
        u.profit = v.profit;
        if (bound(u) > maxprofit)
            Q.push(u);
    }
}

/// Bound
///
/// Textbook was missing some arguments.
float BranchAndBoundSelector::
bound(node u, const int n, const int p[], const int w[], const int W) {
    int j, k;
    int totweight;
    float result;

    if (u.weight >= W)
        return 0;
    else {
        result = u.profit;
        j = u.level + 1;
        totweight = u.weight;
        while (j <= n && totweight + w[j] <= W) {
            totweight = totweight + w[j];
            result = result + p[j];
            j++;
        }

        k = j;
        if (k <= n)
            result = result + (W - totweight) * p[k]/w[k];

        return result;
    }
}
