/* main.cpp
 * --------
 * CSCI 355 Algorithm Analysis
 * Lab 3    Longest Increasing Subsequence
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, February 05, 2019
 *
 * Purpose: 
 */
#include "lis.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> seq1{3,2,6,4,5,1};
    vector<int> seq2{ 1, 12, 7, 0, 23, 11, 52, 31, 61, 69, 70, 2 };

    cout << "PART I — Testing for lis length:\n";
    // Should be 3
    cout << "  "
        << part1::lis_length(seq1) << " (should be 3)" << endl;
    // Should be 7
    cout << "  "
        << part1::lis_length(seq2) << " (should be 7)" << endl
        << endl;


    cout << "PART II — Testing for lis generation\n";

    cout << "  ";
    part2::lis_print(seq1, cout);

    cout << "  ";
    part2::lis_print(seq2, cout);

    return 0;
}
