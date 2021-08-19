/* Filename: array_stats.cpp
 * ------------------
 * Author:  Darwin Jacob Groskleg
 * Date:    Sunday, March 11th, 2018
 * Class:   CSCI 162
 * Assignment:  #3
 */
#include "array_stats.h"
#include <cmath>


/*
 * Calculates the mean points in a result set where the index of an array
 * indicates the number of points and the value at that position indicates the
 * number of times those points were reached.
 */
double arrayIndexMean(int array[], int array_size) {
    double running_sum = 0;
    int value_count = 0;
    for (int i=0; i<array_size; i++) {
        running_sum += i * array[i];
        value_count += array[i];
    }
    return (running_sum/value_count);
}

/*
 * Calculates the sample standard deviation of points in a result set where the
 * index of an array indicates the number of points and the value at that
 * position indicates the number of times those points were reached.
 *
 * s = sqrt( Sum( x - mean)^2 / (N-1) )
 */
double arrayIndexStdDeviation(int array[], int array_size) {
    double mean = arrayIndexMean(array, array_size);
    double ss_differences = 0; // Sum of Squares
    int value_count = 0;

    for (int i=0; i<array_size; i++) {
        for (int j=0; j<array[i]; j++) {
            ss_differences += pow(i - mean, 2);
        }
        value_count += array[i];
    }

    return sqrt(ss_differences / (value_count-1));
}

