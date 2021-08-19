/* main.cpp
 * --------
 * CSCI 355 Algorithm Analysis
 * Lab 4    Memoization Gone Wildcard!
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 26, 2019
 *
 * CONSOLE SAMPLE
 * $> make
 * $> ./bin/lab04 < test/given_tests.in
 * Test Case 1
 *   Phrase:  "abba"
 *   Pattern: "a*a"
 * Match
 *
 * Test Case 2
 *   Phrase:  "abba"
 *   Pattern: "a?a*"
 * No match
 *
 * Test Case 3
 *   Phrase:  "abba"
 *   Pattern: "a**a"
 * Match
 *
 * Test Case 4
 *   Phrase:  "abcba"
 *   Pattern: "*ab?ba*"
 * Match
 *
 * $> ./bin/lab04 < test/given_tests.in 2>/dev/null \
 *      | diff -y - test/given_expected.out
 * Match			Match
 * No match			No match
 * Match			Match
 * Match			Match
 */
#include "Glob.hpp"
#include <iostream>

using namespace std;

bool match(string pattern, int m, string phrase, int n);

int main() {
    int test_cases;
    cin >> test_cases;

    for (int t=1; t<=test_cases; t++) {
        string phrase, pattern;
        cin >> phrase >> pattern;
        clog << "Test Case " << t << '\n'
            << "  Phrase:  \"" << phrase  << "\"\n"
            << "  Pattern: \"" << pattern << "\"\n";
        match(pattern, pattern.size()-1, phrase, phrase.size()-1);
        clog << '\n';
    }

    return 0;
}

/// Prints whether the given pattern matches the phrase.
///     Is just a procedural interface for Glob.
///
/// T(n) = O(n)     where n = size_of_pattern x size_of_phrase
///     See implementation of Glob for analysis.
bool match(string pattern, int m, string phrase, int n) {
    Glob globber(pattern, phrase);                  // T(n) = O(n)
    bool is_match = globber.match(m,n);             // T(n) = O(n)
    if (is_match)
        cout << "Match\n";
    else
        cout << "No match\n";
    return is_match;
}
