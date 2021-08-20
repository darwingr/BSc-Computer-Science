#include <iostream>
#include <cmath>

using namespace std;

bool isPerfect(int);
bool isPerfectFast(int);
void showPerfect(int);

/* This program finds and shows all perfect numbers (between
 * zero and 8000) in a sum equation format.
 * First five are: 6, 28, 496, 8128, 33 550 336.
 */
int main() {
    const int UPPER_BOUND = 8000; // Top of search range
    for (int i = 0; i <= UPPER_BOUND; i++) {
        if (isPerfect(i)) showPerfect(i);
    }

    return 0;
}

/*
 * A positive integer is said to be "perfect" if it is the sum of its proper
 * divisors; that is, the value is equal to the sum of all the numbers (except
 * itself) dividable by it.
 *
 * To check for proper divisors, it should only count from 2 to the number
 * whose square is greater than or equal to the number (1 is always a divisor),
 * adding the divisor and its larger counterpart to the sum.
 *
 * T(n) = O(√n) which is sublinear time, very efficient.
 */
bool isPerfect(int number) {
    // GUARD: perfect numbers must be positive
    //        ond no ONE is perfect.
    if (number <= 1) return false;
    int sum = 1; // all Z+ are divisible by 1

    for (int divisor = 2; divisor <= sqrt(number); divisor++) {
        if (number % divisor == 0) {
            sum += divisor;

            // We can find the remaining proper divisors from the quotients
            // of the proper divisors we already know.
            int quotient = number/divisor;
            if (quotient != divisor) sum += quotient;
        }
    }

    if (sum == number) return true;
    return false;
}

/*
 * Is "as efficient as possible", guaranteed to run in constant time
 * for at least all numbers between 0 and 8000.
 */
bool isPerfectFast(int number) {
    int perfectNums[] = {6, 28, 496, 8128, 33550336}; // Keep sorted
    const int MAX_RANK = sizeof(perfectNums)/sizeof(perfectNums[0]);

    // ASSUMES perfectNums is sorted
    if (number > perfectNums[MAX_RANK-1]) return isPerfect(number);

    for (int p = 0; p < MAX_RANK; p++) {
        if (number == perfectNums[p]) return true;
    }
    return false;
}

/*
 * Outputs the perfect number equation for a given number in the format:
 *      `28 = 1 + 2 + 4 + 7 + 14`
 *
 * Assumes input is perfect.
 *
 * Does not need to (and cannot) be as efficient as isPerfect, since it will
 * only be called a few times given that relatively few numbers in any range
 * will be perfect.
 *
 * T(n) = O(n)
 */
void showPerfect(int number) {
    cout << number << " = 1";
    for (int divisor = 2; divisor <= number/2; divisor++) {
        if (number % divisor == 0) {
            cout << " + " << divisor;
        }
    }
    cout << endl;
}
