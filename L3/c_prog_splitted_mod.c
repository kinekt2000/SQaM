#include "sampler.h"
#include <stdio.h>
#include <math.h>

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
    SAMPLE;
    double x;
    double sum1;
    int i;

    SAMPLE;
    int pieces = 1;
    double delta_x = (upper - lower)/pieces;
    SAMPLE;
    double end_sum = fx(lower) + fx(upper);
    SAMPLE;

    double mid_sum = 0.0;
    double sum = end_sum * delta_x / 2.0;
    SAMPLE;
    do {
        SAMPLE;
        pieces = pieces << 1;
        sum1 = sum;
        delta_x = (upper-lower)/pieces;
        SAMPLE;
        for(i = 1; i <= pieces >> 1; i++)
        {
            SAMPLE;
            x = lower + delta_x * (2.0 * i - 1.0);
            mid_sum = mid_sum + fx(x);
            SAMPLE;
        }
        SAMPLE;
        sum = (end_sum + 2.0 * mid_sum) * delta_x * 0.5;
        SAMPLE;
    } while (fabs(sum - sum1) > fabs(tol*sum));
    SAMPLE;
    return sum;
}

int main(int argc, char **argv) {
    sampler_init(&argc, argv);
    lower = 1.0;
    upper = 9.0;
    double sum = trapez(lower,upper,tol);
    // printf("area= %.16e\n", sum);
    return 0;
}
