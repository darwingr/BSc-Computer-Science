/* Glob.hpp
 * --------
 * CSCI 355 Algorithm Analysis
 * Lab 4    Memoization Gone Wildcard!
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 26, 2019
 *
 * Purpose: an interface to the Glob object.
 */
#ifndef GLOB_HPP_INCLUDED
#define GLOB_HPP_INCLUDED

#include "MaybeMatrix.hpp"
#include <string>

/// Glob
///
/// Serves to determine if a pattern containing wildcard characters (*, ?)
/// can be expanded, or `globbed`, to match the given phrase.
///
class Glob {
    const std::string pattern;
    const std::string phrase;

public:
    /// constructor
    ///
    /// T(n) = O(n)     where n = size_of_pattern x size_of_phrase
    ///
    Glob(std::string pattern_, std::string phrase_) :
        pattern{ pattern_ },
        phrase{ phrase_ },
        memos(pattern.size(), phrase.size())                // T(n) = O(n)
    {}



    /// match
    ///
    /// Returns whether the given pattern matches to the phrase.
    ///
    /// T(n) = O(n)     where n = size_of_pattern x size_of_phrase
    ///
    bool match();
    bool match(int m, int n);


private:
    /// An MxN matrix for storing memoized subproblems for the match(m, n).
    MaybeMatrix<bool> memos;

    /// memoize
    ///
    /// Returns the given value after ensuring something has been memoized
    /// for (m, n).
    ///
    /// T(n) = O(1)
    ///
    bool memoize(int m, int n, bool return_value);
};

#endif // GLOB_HPP_INCLUDED
