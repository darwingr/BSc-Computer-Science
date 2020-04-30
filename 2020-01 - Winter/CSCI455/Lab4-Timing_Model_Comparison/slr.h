/* slr.h
 * -----
 * Authors: Darwin Jacob Groskleg (2020)
 *
 * Purpose: do simple linear regression.
 */
#ifndef SLR_H_INCLUDED
#define SLR_H_INCLUDED

typedef struct {
    double a; /* intercept */
    double b; /* slope */
} slr_equation_t;

slr_equation_t slr_find_line(int n, int X[], double Y[]);

double slr_predict(slr_equation_t eqt, int x);

#endif /* SLR_H_INCLUDED */
