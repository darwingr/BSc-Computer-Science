/* lis.hpp
 * -------
 * CSCI 355 Algorithm Analysis
 * Lab 3    Longest Increasing Subsequence
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 05, 2019
 *
 * Purpose: 
 */
#ifndef LIS_HPP_INCLUDED
#define LIS_HPP_INCLUDED

#include <vector>
#include <deque>

/// Part I: Longest Increasing Subsequence Length
///
/// Exercises:
///     1. Write a LIS algorithm using this dynamic programming approach to
///        return the length of the LIS for a sequence passed as an argument.
///
/// Questions:
///     1. Does the Principle of Optimality apply to the brute force solution?
///
///         YES, since at each element in the sequence the optimal solution to
///         that instance of the problem always contains optimal solutions to
///         sub-instances of the problem, those elements occurring prior in the
///         sequence.
///
///     2. What is the efficiency of your algorithm?
///
///         T(n) = O(n^2) <- theta, not big-O
///         See implementation for analysis.
///
namespace part1 {

    /// Return the length of the LIS for a sequence passed as an argument.
    ///
    int lis_length(std::vector<int> sequence);

}; // part1



/// Part II: LIS Generation
///
/// Exercises:
///     1. Add to your algorithm above the ability to output an optimal solution.
///     2. Create a function that will print the optimal subsequence in order,
///        given prev[ n ], length[ n ], and the index position of a maximum
///        value in length[ n ].
///
/// Questions:
///     1. Does adding this feature change the efficiency of the algorithm?
///
///         The efficiency of the algorithm is of the same order as in part I,
///         that is T(n) = O(n^2).
///         See implementation for analysis.
///
namespace part2 {

    /// lis_generate
    ///
    /// Outputs the optimal solution arrived at by from part1::lis_length.
    ///
    std::deque<int> lis_generate(const std::vector<int>& sequence);

    /// lis_print
    ///
    /// Prints the optimal subsequence in order, given prev[ n ], length[ n ],
    /// and the index position of a maximum value in length[ n ].
    ///
    void lis_print(std::vector<int> vec, std::ostream& out);

}; // part2


#endif // LIS_HPP_INCLUDED
