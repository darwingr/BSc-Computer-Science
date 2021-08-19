/* loot.hpp
 * --------
 * CSCI 355 Algorithms Analysis
 * Lab 7    A Knapsack of Algorithms
 *
 * Authors: Darwin Jacob Groskleg, Martin van Bommel (where indicated)
 * Date:    Tuesday, March 26, 2019
 */
#ifndef LOOT_HPP_INCLUDED
#define LOOT_HPP_INCLUDED

struct loot {
    const int     value = 0; // worthless
    const double weight = 1; // 1 unit
};

/// < Less Than
///
/// Compares on the basis of $ per unit of weight.
/// Sufficient for sorting.
inline bool operator< (const loot& lhs, const loot& rhs) {
    return (lhs.value/lhs.weight) < (rhs.value/rhs.weight);
}

/// == Equality
///
/// Equality comparison on basis of attributes, identity is not considered.
inline bool operator==(const loot& lhs, const loot& rhs) {
    return lhs.value  == rhs.value
        && lhs.weight == rhs.value;
}

#endif // LOOT_HPP_INCLUDED
