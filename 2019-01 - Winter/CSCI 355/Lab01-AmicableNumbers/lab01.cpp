/* lab01.cpp
 * ---------
 * CSCI 355 — Algorithm Analysis
 * Lab 1    — Amicable Numbers
 * Authors: Darwin Jacob Groskleg, Martin van Bommel
 * Date:    Tuesday, January 15, 2019
 *
 * Purpose: to learn the futility and pointlessness of doing every case
 *          complexity analysis of an algorithm.
 */
#include <iostream>
#include "strmanip.hpp"
#include "benchmark_set.hpp"

using namespace std;

// NOTE on namespaces use:
//  - needed to avoid conflicts between questions that ask to redefine existing
//    functions without losing the old definition,
//  - make it clear what question a function relates to.
namespace a { bool amicable(int, int);  };
namespace b { void pairs(int);          };
namespace c { void pairs(int);          };
namespace d { bool amicable(int, int);  };
namespace e { int  divisorsum(int);     };
namespace f { void fastpairs(int);      };

int main() {
    const int n = 1000;

    cout << section_underline("Question b. Amicable pairs under: ", n);
    b::pairs(n);

    cout << section_underline("Question c. Unique Pairs: ", n);
    c::pairs(n);

    cout << section_underline("Question d. Faster Amicable:") << boolalpha
        << d::amicable(n, n)     << print_pair(n, n)     << endl
        << d::amicable(1, 1)     << print_pair(1, 1)     << endl
        << d::amicable(220, 284) << print_pair(220, 284) << endl
        << d::amicable(220, 220) << print_pair(220, 220) << endl;

    cout << section_underline("Question f. Fastpairs: ", 10000);
    f::fastpairs(10000);

    cout << "\nQuestion G:" << endl;
    BenchmarkSet<void,int> test_pairs{ {
        { b::pairs,     "b::pairs(n)" },
        { c::pairs,     "c::pairs(n)" },
        { f::fastpairs, "f::fastpairs(n)" }
    }};
    test_pairs.with({ 5000, 10000}).print_results();

    return 0;
}

/// Amicable
/// Determines if its two parameters are amicable.
///
/// Defn 1: AMICABLE NUMBERS are 2 different numbers where the sum of the proper
///         divisors of each is equal to the other number.
///
/// Defn 2: a PROPER DIVISOR of a number is a positive factor (evenly divides
///         into it) of that number other that the number itself.
///
bool a::amicable(int x, int y) {
    int sumx = 1, sumy = 1;

    for (int i = 2; i < x; i++)
        if (x % i == 0)
            sumx += i;

    for (int i = 2; i < y; i++)
        if (y % i == 0)
            sumy += i;

    return (sumx == y && sumy == x);
}

/// Pairs
/// Finds all the amicabe pairs that exist for numbers < n.
///
void b::pairs(int n) {
    for (int i=1; i<n; i++)
        for (int j=1; j<n; j++)
            if (a::amicable(i,j))
                cout << i << ' ' << j << endl;
}

/// Question C: Improved Pairs
/// Improvement on Pairs so that it:
///     1. only returns one copy of each pair,
///     2. does not call amicabl twice for each pair of values.
///
void c::pairs(int n) {
    for (int i=1; i<n; i++)
        for (int j=i; j<n; j++)
            if (a::amicable(i,j))
                cout << i << ' ' << j << endl;
}


/// Question D: Improved Amicable
/// Improvement on Amicable so that:
///     1. It only counts up to the square root of each value,
///     2. It checks if "sumx = y" before starting the 2nd for loop.
///
///     3. BONUS RULE: both numbers in a pair must be different to be amicable,
///        as per the intro paragraph to the lab, also Defn 2 above.
///
bool d::amicable(int x, int y) {
    if (x == y) return false;
    int sumx = 1, sumy = 1;

    // Same as
    // for (int i=2; i <= std::sqrt(x); i++)
    for (int i = 2; i*i < x; i++)
        if (x % i == 0)
            sumx += i + x/i;

    if (sumx != y) return false;        // give up early

    for (int i = 2; i*i < y; i++)
        if (y % i == 0)
            sumy += i + y/i;

    return (sumx == y && sumy == x);    // we check again, that's fine
}

/// Question E: Divisorsum
///
/// Calculates the sum of the proper divisors of its one input parameter as
/// efficiently as possible.
///
int e::divisorsum(int n) {
    int sum = 1;
    for (int i = 2; i*i < n; i++)
        if (n % i == 0)
            sum += i + n/i;

    return sum;
}


/// f:amicable
///
/// Helper function for a tidier call to e::divisorsum in fastpairs.
///
namespace f {
bool amicable(int x, int y) {
    return (x != y
        &&  e::divisorsum(x) == y
        &&  e::divisorsum(y) == x);
}
} // namespace f

/// Question F: Fastpairs
///
/// Uses `divisorsum` to much more efficiently find the amicable pairs that
/// exist for numbers < n.
///
/// New rule: both numbers in a pair must be different.
///
void f::fastpairs(int n) {
    for (int i=1; i<n; i++)
        for (int j=i; j<n; j++)
            if (f::amicable(i, j))
                cout << i << ' ' << j << endl;
}
