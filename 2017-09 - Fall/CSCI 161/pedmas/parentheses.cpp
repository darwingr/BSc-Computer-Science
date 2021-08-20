/*
 * compile to assembly using:
 * g++ -S parentheses.cpp
 */
#include <iostream>

int main() {
    std::cout << "99 - 9 / 2 + 7 * (8 / 2) gives: "
              << 99 - 9 / 2 + 7 * (8 / 2)
              << std::endl << std::endl;

    std::cout << "With parentheses omitted we're sure 9/2 runs first,\n"
              << "99 - 9 / 2 + 7 * 8 / 2 gives: "
              << 99 - 9 / 2 + 7 * 8 / 2
              << std::endl << std::endl;

    float in_parentheses = 8 / 2;
    std::cout << "But caculating the value in parentheses explicitly and \n"
              << "assigning it to a variable then calculating the expression \n"
              << "we get: "
              << 99 - 9 / 2 + 7 * in_parentheses
              << std::endl << std::endl;

    return 0;
}
