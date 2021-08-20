/*
 * compile to assembly using:
 * g++ -S parentheses.cpp
 */

#include <iostream>

//#define EXPR    (99 - 9 / 2 + 7 * (8 / 2))

int main() {
    std::cout << (3 + -2) << std::endl;
    //return EXPR;
    return 0;
}
