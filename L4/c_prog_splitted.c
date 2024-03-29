#include "sampler.h"
#include <stdio.h>
#include <math.h>

/* integration by the trapezoidal rule */

const double tol = 1.0e-6;
double sum, upper, lower;

/* find f(x)=1/x */
/* watch out for x=0 ! */
double fx(double x) {
    return 1.0/x;
}

/* numerical integration by the trapezoid method */
/* function is FX, limits are LOWER and UPPER */
/* with number of regions equal to PIECES */
/* fixed partition is DELTA_X, answer is SUM */
void trapez(double lower, double upper, double tol, double* sum) {
    SAMPLE;
    int pieces, i;
    double x, delta_x, end_sum, mid_sum, sum1;

    SAMPLE;
    pieces = 1;
    delta_x = (upper - lower)/pieces;
    SAMPLE;
    end_sum = fx(lower) + fx(upper);
    SAMPLE;
    *sum = end_sum * delta_x / 2.0;
    mid_sum = 0.0;
    SAMPLE;
    do {
        SAMPLE;
        pieces = pieces*2;
        sum1 = *sum;
        delta_x = (upper-lower)/pieces;
        SAMPLE;
        for(i = 1; i <= pieces / 2; i++)
        {
            SAMPLE;
            x = lower + delta_x * (2.0 * i - 1.0);
            mid_sum = mid_sum + fx(x);
            SAMPLE;
        }
        SAMPLE;
        *sum = (end_sum + 2.0 * mid_sum) * delta_x * 0.5;
        SAMPLE;
    } while ( fabs(*sum - sum1) > fabs(tol*(*sum)));
    SAMPLE;
}

int main(int argc, char **argv) {
    sampler_init(&argc, argv);
    lower = 1.0;
    upper = 9.0;
    trapez(lower,upper,tol,&sum);
    // printf("area= %.16e\n", sum);
    return 0;
}
