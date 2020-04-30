/* random.h
 * --------
 * Credit:  Dr. Martin van Bommel
 * Authors: Dr. Martin van Bommel, Darwin Jacob Groskleg
 * Modified from CSCI 162 / Assig 3
 */
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <stdbool.h>

/*
 * Function: Randomize
 * Usage: Randomize();
 * -------------------
 * This function sets the random seed so that the random sequence
 * is unpredictable.  During the debugging phase, it is best not
 * to call this function, so that program behavior is repeatable.
 * Otherwise only call it once at the start of use of random values.
 *
 * Only needs to be called once per process.
 */
extern void Randomize();
extern void RandomizeWithOffset(int seed_offset);
extern void RandomizeSeedWithOffset(int seed_offset, unsigned int seed);

/*
 * Function: RandomInteger
 * Usage: i = RandomInteger(low, high);
 * ------------------------------------
 * This function returns an integer in the closed interval [low..high],
 * meaning that the result is greater than or equal to low and less than
 * or equal to high, with each value having equal probability.
 */
extern int RandomInteger(int low, int high);

/*
 * Function: RandomReal
 * Usage: d = RandomReal(low, high);
 * ---------------------------------
 * This function returns a random real number in the half-open
 * interval [low .. high), meaning that the result is always
 * greater than or equal to low but strictly less than high.
 */
extern double RandomReal(double low, double high);

/*
 * Function: RandomChance
 * Usage: if (RandomChance(p)) . . .
 * ---------------------------------
 * The RandomChance function returns true with the probability
 * indicated by p, which should be a floating-point number between
 * 0 (meaning never) and 1 (meaning always).  For example, calling
 * RandomChance(.30) returns true 30 percent of the time.
 */
extern bool RandomChance(double probability);

/*
 * Function: RandomNormal
 * Usage: n = RandomNormal(mean, std);
 * -----------------------------------
 * This function returns a random real number following the
 * normal distribution with given mean and standard deviation (std).
 */
double RandomNormal(double mean, double std);

#endif /* RANDOM_H_INCLUDED */
