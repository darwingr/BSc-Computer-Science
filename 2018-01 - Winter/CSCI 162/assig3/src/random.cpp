/* File: random.cpp
 * ----------------
 * Credit: Dr. Martin van Bommel
 *
 * This file implements the random.h interface.
 */
#include "random.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

//using namespace std;

/*
 * Function: Randomize
 * Usage: Randomize();
 * -------------------
 * This function sets the random seed using the system time
 * so that the random sequence is unpredictable.
 */
void Randomize()
{
    srand(time(NULL));
}

/*
 * Function: RandomInteger
 * -----------------------
 * This function first obtains a random integer in
 * the range [0..RAND_MAX] and converts it into an
 * integer in the range [low..high] by applying the
 * four steps:
 * (1) Generate a real number between 0 and 1.
 * (2) Scale it to the appropriate range size.
 * (3) Truncate the value to an integer.
 * (4) Translate it to the appropriate range.
 */
int RandomInteger(int low, int high)
{
    int k;
    double d;

    d = (double) rand() / ( (double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}

/*
 * Function: RandomReal
 * Usage: d = RandomReal(low, high);
 * ---------------------------------
 * This function returns a random real number in the half-open
 * interval [low .. high).  The function first obtains a random
 * integer in the range [0..RAND_MAX] and converts it
 * by applying the steps:
 * (1) Generate a real number between 0 and 1.
 * (2) Scale it to the appropriate range size.
 * (4) Translate it to the appropriate range.
 */
double RandomReal(double low, double high)
{
    double d;

    d = (double) rand() / ( (double) RAND_MAX + 1);
    return (low + d * (high - low));
}

/*
 * Function: RandomChance
 * Usage: if (RandomChance(p)) . . .
 * ---------------------------------
 * The RandomChance function returns true with the probability
 * indicated by p, which should be a floating-point number between
 * 0 (meaning never) and 1 (meaning always).
 */
bool RandomChance(double probability)
{
    return (RandomReal(0,1) < probability);
}

/*
 * Function: RandomNormal
 * Usage: n = RandomNormal(mean, std);
 * -----------------------------------
 * This function returns a random real number following the
 * normal distribution with given mean and standard deviation (std)
 * using the Box-Muller Method.
 */
double RandomNormal(double mean, double std)
{
    double u1 = RandomReal(0,1);
    double u2 = RandomReal(0,1);

    double z = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);

    return mean + std*z;
}

