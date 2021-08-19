/* main.cpp
 * --------
 * CSCI 355 — Algorithm Analysis
 * Lab 2    — Making Dynamic Change
 *
 * Authors: Darwin Jacob Groskleg
 * Date:    Tuesday, January 29, 2019
 *
 * Purpose: Test the 3 different implementations for counting change.
 */
#include "change.hpp"

#include <iostream>
#include <vector>

using namespace std;

void test_part1();
void test_part2();
void test_part3();
void print(vector<int> Q);


int main() {
    test_part1();
    test_part2();
    test_part3();

    return 0;
}


// SLOW when big!
void test_part1() {
    cout << "\nTesting Part 1" << endl;

    cout << "For D={ 1, 5, 10, 25, 100, 200 }, Change for 1, 3 & 368 cents:\n";
    print( Part1::quantities_for(  1, { 1, 5, 10, 25, 100, 200 }) );
    print( Part1::quantities_for(  3, { 1, 5, 10, 25, 100, 200 }) );
    print( Part1::quantities_for(368, { 1, 5, 10, 25, 100, 200 }) );

    cout << "\nFor D={ 1, 5, 8, 10, 25 }\n";
    cout << "Coins for 16 cents: "
        << Part1::coins_for( 16, { 1, 5, 8, 10, 25 });
    print( Part1::quantities_for( 16, { 1, 5, 8, 10, 25 }) );

    cout << "Coins for 169 cents: "
        << Part1::coins_for( 169, { 1, 5, 8, 10, 25 });
    print( Part1::quantities_for( 169, { 1, 5, 8, 10, 25 }) );

    cout << '\n' << '\n';
}

// SLOW but better than part I
void test_part2() {
    cout << "Testing Part 2" << endl;

    cout << "For D={ 1, 5, 8, 10, 25 }\n";
    cout << "Coins for 16 cents: "
        << Part2::least_coins_for(16, { 1, 5, 8, 10, 25 })
        << " should be 2.\n";

    cout << "Coins for 169 cents: "
        << Part2::least_coins_for(169, { 1, 5, 8, 10, 25 })
        << " should be ?.\n";

    cout << '\n';
}


void test_part3() {
    cout << "Testing Part 3" << endl;

    cout << "For D={ 1, 5, 8, 10, 25 }\n";
    cout << "Coins for 16 cents: "
        << Part3::least_coins_for(16, { 1, 5, 8, 10, 25 })
        << " should be 2.\n";

    cout << "Coins for 169 cents: "
        << Part3::least_coins_for(169, { 1, 5, 8, 10, 25 })
        << " should be ?.\n";

    cout << '\n';
}


void print(vector<int> Q) {
    cout << "    Q={ ";
    for (auto& q : Q) cout << q << ' ';
    cout << '}'<< endl;
}

