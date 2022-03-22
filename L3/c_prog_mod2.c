#include "sampler.h"
#include <stdio.h>
#include <math.h>

#ifndef SAMPLE
#define SAMPLE
#endif

/* integration by the trapezoidal rule */


const double tol = 1.0e-6;
double upper, lower;

/* find f(x)=1/x */
/* watch out for x=0 ! */
double fx(double x) {
    return 1.0/x;
}

/* numerical integration by the trapezoid method */
/* function is FX, limits are LOWER and UPPER */
/* with number of regions equal to PIECES */
/* fixed partition is DELTA_X, answer is SUM */
double trapez(double lower, double upper, double tol) {
    double x;
    int i;
    double added_sum;
    
    int nseg = 1;
    double dx = (upper - lower) / nseg;

    double sum = 0.5 * (fx(lower) + fx(upper));

    double old_ans = 0.0;
    double ans = sum * dx;

    double err_est = fmax(1.0, fabs(tol * ans));
    while(err_est > fabs(tol * ans)) {
        old_ans = ans;
        dx = (upper - lower) / nseg;
        x = lower + 0.5 * dx;
        added_sum = 0.0;

        for (i = 0; i < nseg; i++) {
            added_sum += fx(x + i * dx);
        }

        sum += added_sum;
        nseg *= 2;
        ans = sum * 0.5 * dx;
        err_est = fabs(old_ans - ans);

    }
    return ans;
}

int main(int argc, char **argv) {
    sampler_init(&argc, argv);
    SAMPLE;
    lower = 1.0;
    upper = 9.0;
    double sum = trapez(lower,upper,tol);
    SAMPLE;
    // printf("area= %.16e\n", sum);
    return 0;
}
