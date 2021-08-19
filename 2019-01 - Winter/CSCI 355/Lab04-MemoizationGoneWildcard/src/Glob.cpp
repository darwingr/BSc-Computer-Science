/* Glob.cpp
 * --------
 * CSCI 355 Algorithm Analysis
 * Lab 4    Memoization Gone Wildcard!
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 26, 2019
 *
 * Purpose: the implementation of Glob.
 */
#include "Glob.hpp"
#include <cassert>

bool Glob::match() {
    return Glob::match(pattern.size()-1, phrase.size()-1);
}

/// match
///
/// ANALYSIS
///     where n' = size_of_pattern x size_of_phrase
///              = m x n
///
///   TRYING THE MASTER METHOD
///     Worst case for dividing and combining, f(n') is the last of the base
///     cases with a large m: f(n') = W(m).
///     Since we use memoization this would only ever happen once in the entire
///     greater problem, thus f(n) = O(1).
///
///     The problem may divide in to 2 subproblems, so a = 2.
///     In that case (and the others, mostly) the subproblem size is n-1.
///     So  n' - 1    = n'/b
///         b(n' - 1) = n'
///         b = n'/(n' - 1)
///         ...so b is not constant,
///         CAN'T USE MASTER METHOD.
///
///
///   THINKING ABOUT TREES & SUBPROBLEM OVERLAP
///     Any base case is solved in constant time.
///     Each recursize call case has f(n') = O(1),
///     and will recurse again until it either:
///         1. hits a base case,
///         2. reaches a memoized result.
///     Then it memoizes all values going back up.
///     Thus, no subproblem is ever computed more than once.
///     Since there are m x n subproblems we have the follwing:
///
///     T(n') =     O(m * n)    can't do worse than this
///           = OMEGA(m * n)    can't do asymptotically better than this
///           = THETA(m * b)    since big-O == big-omega
///
bool Glob::match(const int m, const int n) {
    // Exit early with a memo
    if (memos.has(m, n))
        return memos.value(m, n);

// BASE CASES (not memoizable)

    // If m < 0 and n < 0,
    //      return true – both reached the end
    if (m < 0 && n < 0)
        return true;
    // If m < 0 and n >= 0,
    //      return false – only pattern reached end
    if (m < 0 && n >=0)
        return false;
    // If n < 0 and m >= 0,
    //      return true only if remaining characters in pattern are all ‘*’
    if (n < 0 && m >= 0) {
        for (int i=0; i<=m; i++)
            if (pattern.at(i) != '*')
                return false;
        return true;
    }



    // Closure to be concise
    auto memoize = [this, &m, &n] (bool return_value) {
        return this->memoize(m, n, return_value);
    };

// RECURSIVE CASES

    // If pattern[m] == ‘*’, return true only if either:
    //      pattern[0..m] matches phrase[0..n-1], 
    //      OR pattern[0..m-1] matches phrase[0..n]
    if (pattern.at(m) == '*')
        return memoize( match(m, n-1) || match(m-1, n) );

    // If pattern[m] == ‘?’, return true only if
    //      pattern[0..m-1] matches phrase[0..n-1]
    if (pattern.at(m) == '?')
        return memoize( match(m-1, n-1) );

    // Otherwise return true only if both
    //      pattern[m] == phrase[n]
    //      AND pattern[0..m-1] matches phrase[0..n-1]
    else
        return memoize( (pattern.at(m) == phrase.at(n)) && match(m-1, n-1) );
}

/// memoize
///
/// This method IS idempotent but not in respect to the value of return_value,
/// only that there is a guarantee something must then be at any valid position
/// matric(m, n).
bool Glob::memoize(int m, int n, bool return_value) {
    if (!memos.has(m, n))
        memos.emplace(m, n, return_value);
    // Must Fail: The matrix is mutable, our memos should not be.
    assert( (memos.value(m, n) == return_value)
        && "Return value differs from memoed value.");
    return return_value;
}
