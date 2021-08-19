/* prime.hpp
 * ---------
 * Authors: Darwin Jacob Groskleg
 * Date:    Wednesday, January 23, 2019
 *
 * Purpose: 
 *
 * Approaches:
 *  1. Store bool values in a bitarray for all the positive 64-bit integers,
 *     marking true at addresses of integers that are prime.
 *     How much space?
 *      (2^63 - 1) * 2 states  /
 *      --------------------- / 1,000,000,000,000 bytes/Terabyte
 *           8 bits/byte     /
 *
 *      = 2,305,843 Terabytes (roughly) Too Big!
 *
 *  2. Precompute all the primes up to (2^63 - 1) and store them in an array.
 *     Then just search the array.
 *     How much space?
 *      - There are 203,280,221 primes in the positive 32-bit integer space.
 *          (32 bits * 203,280,221)   /
 *          -----------------------  / 1,000,000 bytes/Gigabyte
 *                8 bits/byte       /
 *
 *          = 813.121 Megabytes (roughly)
 */
#ifndef PRIME_HPP_INCLUDED
#define PRIME_HPP_INCLUDED

#include <array>

constexpr static std::array<int> integer_primes {sieve_of_erastosthenes()};

#endif // PRIME_HPP_INCLUDED
