/* slr.c
 * -----
 * Authors: Darwin Jacob Groskleg (2020)
 *
 * Purpose: do simple linear regression.
 */
#include "slr.h"

#include <assert.h>
#include <math.h>

double regression_coefficient(int, double, double, double, double);
double y_intercept(int, double, double, double);


double slr_predict(slr_equation_t eqt, int x) {
    /*  intercept  +  slope * x    */
    return  eqt.a  +  eqt.b * x;
}

/* let K = n
 * for each (x, y) of K:
 *      x^2, xy
 *  calc slope:
 *      m =  (K * SUM(xy) - SUM(x)*SUM(y))
 *         / (K * SUM(x^2) - SUM(x)^2)
 *  calc intercept:
 *      b = (SUM(y) - m*SUM(x))/K
 *
 * passes as pointer, NOT COPY
 */
slr_equation_t slr_find_line(int n, int X[], double Y[]) {
    //assert() len(X) == len(Y) == n
    slr_equation_t eqt;
    double sigma_x  = 0;
    double sigma_xx = 0;
    double sigma_y  = 0;
    double sigma_xy = 0;
    for (int i=0; i<n; i++) {
        sigma_x  += X[i];
        sigma_xx += pow(X[i], 2);
        sigma_y  += Y[i];
        sigma_xy += X[i] * Y[i];
    }
    double slope = regression_coefficient(n, sigma_x, sigma_xx,
                                             sigma_y, sigma_xy);
    eqt.a = y_intercept(n, slope, sigma_x, sigma_y);
    eqt.b = slope;
    return eqt;
}

/* Slope aka "Regression Coefficient"
 *
 * Biostatistical Analysis 5ed, JH Zar, Pages 330-337
 *  Yi = a + BXi for best fit using least squares linear regression.
 *
 */
double regression_coefficient(
        int    data_points,
        double sum_of_x,        // SUM x
        double sum_sqr_of_x,    // SUM xx
        double sum_of_y,        // SUM y
        double sum_of_xy)       // SUM xy
{
    double sum_of_cross_products = sum_of_xy - sum_of_x * sum_of_y/data_points;
    double sum_of_squares_x = sum_sqr_of_x - pow(sum_sqr_of_x, 2)/data_points;
    return sum_of_cross_products / sum_of_squares_x;
}

double y_intercept(
        int    data_points,
        double slope,
        double sum_of_x,
        double sum_of_y)
{
    return (sum_of_y - slope * sum_of_x) / data_points;
}
