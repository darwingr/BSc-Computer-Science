#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// CHALLENGE: can arbitrary turing machine assignment, originally written in
// ruby, be written in the same amount of legible code in C++?
// I think its doable.
int main() {
    // need to test string ability
    // prepending, appending, accessing, getting length, hex to int

    string hex_string = "C"; // should be 12
    int decimal = strtoul(hex_string.c_str(), NULL, 16);
    cout << "String \"" << hex_string << "\" is " << decimal << endl;

    string tape = "abba";
    cout << "String: |" << tape << '|' << endl;

    tape.append("X");
    cout << "Appended X: |" << tape << '|' << endl;

    tape.insert(0, "X");
    cout << "Prepended X: |" << tape << '|' << endl;

    return 0;
}
