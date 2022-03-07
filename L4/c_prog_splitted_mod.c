#include "sampler.h"
#include <stdio.h>
#include <math.h>

const double tol = 1.0e-6;
double upper, lower;

double fx(double x)
{
    return 1.0 / sqrt(x);
}

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
    // pieces = 1;
    // delta_x = (upper - lower)/pieces;
    // SAMPLE;
    // end_sum = isqrt(lower) + isqrt(upper);
    // SAMPLE;
    // *sum = end_sum * delta_x / 2.0;
    // mid_sum = 0.0;
    // SAMPLE;
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
    // printf("\n");
    double sum = trapez(lower,upper,tol);
    // printf("\n");
    // printf("area= %.16e\n", sum);
    return 0;
}
