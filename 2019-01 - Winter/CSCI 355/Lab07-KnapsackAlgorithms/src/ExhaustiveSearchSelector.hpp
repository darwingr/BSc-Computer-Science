/* ExhaustiveSearchStrategy.hpp
 * ----------------------------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#ifndef EXHAUSTIVESEARCHSTRATEGY_HPP_INCLUDED
#define EXHAUSTIVESEARCHSTRATEGY_HPP_INCLUDED

#include <vector>
#include <cmath>
#include "SubsetSelectionAlgorithm.hpp"
#include "loot.hpp"

/// Just try every combination of items - O(2^n)
class ExhaustiveSearchStrategy : public SubsetSelectionAlgorithm {
public:
    inline auto
    most_valuable_subset(int weight_limit, std::vector<loot> lootable_items)
        -> std::vector<loot>
    {
        std::vector<bool> permutations( lootable_items.size(), false);
        auto best_perm_so_far {permutations};
        int  best_value_so_far = 0;
        for (int i=0; i<pow(2,lootable_items.size()); i++) {
            int    perm_value  = 0;
            double perm_weight = 0;
            for (size_t k=0; k<permutations.size(); k++) {
                perm_value +=   permutations.at(k)
                            * lootable_items.at(k).value;
                perm_weight +=  permutations.at(k)
                            * lootable_items.at(k).weight;
            }

            // Item set fits and is more valuable?
            if (perm_weight <= weight_limit
            &&  perm_value  >  best_value_so_far) {
                best_perm_so_far  = permutations;
                best_value_so_far = perm_value;
            }

            increment_permutation_array(permutations);
        }

        // fill the knapsack
        std::vector<loot> best;
        for (size_t l=0; l<best_perm_so_far.size(); l++)
            if (best_perm_so_far.at(l))
                best.push_back(lootable_items.at(l));

        return best;
    }

private:
    // expects each element to be false
    inline void increment_permutation_array(std::vector<bool> & perm) {
        bool carry = true;
        for (size_t i=0; i<perm.size(); i++) {
            if (carry) {
                if (perm.at(i) == 0) {
                    perm.at(i) = 1;
                    carry = false;
                } else {
                    perm.at(i) = 0;
                    // carry is still true
                }
            }
        }
    }
};

#endif // EXHAUSTIVESEARCHSTRATEGY_HPP_INCLUDED
