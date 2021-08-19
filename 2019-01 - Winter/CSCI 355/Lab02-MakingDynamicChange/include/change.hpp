/* change.hpp
 * ----------
 * CSCI 355 — Algorithm Analysis
 * Lab 2    — Making Dynamic Change
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 29, 2019
 *
 * Purpose: interface for algorithms that convert units of money in cents
 *          to the appropriate amount of change in denominated coins.
 *
 * Definitions:     cents   = units of money
 *                  coins   = denominated money
 *                  pennies = a 1 cent denominated coin
 *                  change  = equivalent units of money in a set of coins
 */
#ifndef CHANGE_HPP_INCLUDED
#define CHANGE_HPP_INCLUDED
#include <vector>

/// Part I — The Greedy Approach
namespace Part1 {

/// quantities_for
///
/// Returns the quantities of each denomination specified that add up to the
/// given target amount in cents.
///
std::vector<int>
quantities_for(int cents, const std::vector<int> denominations);

/// coins_for
///
/// Returns the number of coins that could be given out in change for
/// a target amount of cents using specified denominations.
int coins_for(const int cents, std::vector<int> denominations);

}; // Part1



/// Part II — The Recursive Approach
namespace Part2 {

/// least_coins_for
///
/// Returns the smallest number of coins that could be given out in change for
/// a target amount cents using specified denominations.
///
/// Same as `coins_for` Part I but is concerned with computing the smallest
/// number that is possible.
///
int least_coins_for(const int cents, std::vector<int> denominations);

}; // Part2



/// Part III — Dynamic Programming Approach
namespace Part3 {

/// least_coins_for
///
/// Returns the smallest number of coins that could be given out in change for
/// a target amount cents using specified denominations.
///
/// Same as `least_coins_for` in Part II.
///
int least_coins_for(const int cents, const std::vector<int> denominations);

}; // Part3


#endif // CHANGE_HPP_INCLUDED
