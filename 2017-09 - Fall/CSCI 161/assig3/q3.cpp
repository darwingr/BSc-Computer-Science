#include <iostream>
#include <iomanip>

using namespace std;

/* The Sieve of Erastosthenes!
 *
 * This program finds all the prime numbers below some set upper bound, 1000 in
 * this case. It does so by iterating through an array, setting all following
 * numbers to 0 if they're divisible by the current non-zero number.
 */
int main() {
    const int UPPER_BOUND = 1000;
    const int SIEVE_SIZE = UPPER_BOUND + 1;
    int sieve[SIEVE_SIZE] = {0, 0}; // 0 and 1 are not prime
    int prime_count = 0;

    // Fill the sieve: Set initial values
    for (int i = 2; i < SIEVE_SIZE; i++) sieve[i] = i;

    // Shake the sieve: Find and zero out the non-prime values
    for (int i = 0; i < SIEVE_SIZE; i++) {
        if (sieve[i] != 0) {
            for (int composite = i*i; composite < SIEVE_SIZE; composite += i) {
                sieve[composite] = 0;
            }
            prime_count++;
        }
    }

    // Show what's left: Print the primes, the non-zero values
    cout << "Found "<< prime_count << " primes!" << endl
         << "Grouped by hundreds below: " << endl;
    for (int i = 0; i < SIEVE_SIZE; i++) {
        if (i % 100 == 0) cout << endl;
        if (sieve[i] != 0) {
            cout << setw(4) << i;
        }
    }

    return 0;
}
