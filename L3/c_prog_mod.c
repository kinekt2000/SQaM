#include "sampler.h"
#include <math.h>

/* integration by the trapezoidal rule */

const double  tol = 1.0E-6;
double sum,upper,lower;

/* find f(x)=1/x */
/* watch out for x=0 ! */
double fx(double x) {
    return 1.0/x;
}


double trapezoid(double lower, double upper, double tol) {
    SAMPLE;
    double x;
    int i;
    double added_sum;
    
    SAMPLE;
    int nseg = 1;
    double dx = (upper - lower) / nseg;

    SAMPLE;
    double sum = 0.5 * (fx(lower) + fx(upper));

    SAMPLE;
    double old_ans = 0.0;
    double ans = sum * dx;

    SAMPLE;
    double err_est = fmax(1.0, fabs(tol * ans));
    while(err_est > fabs(tol * ans)) {
        SAMPLE;
        old_ans = ans;
        dx = (upper - lower) / nseg;
        x = lower + 0.5 * dx;
        added_sum = 0.0;

        SAMPLE;
        for (i = 0; i < nseg; i++) {
            added_sum += fx(x + i * dx);
        }

        SAMPLE;
        sum += added_sum;
        nseg *= 2;
        ans = sum * 0.5 * dx;
        err_est = fabs(old_ans - ans);

        SAMPLE;
    }
    return ans
}

/* numerical integration by the trapezoid method */
/* function is FX, limits are LOWER and UPPER */
/* with number of regions equal to PIECES */
/* fixed partition is DELTA_X, answer is SUM */
void trapez(double lower, double upper, double tol, double* sum) {
    int pieces, i;
    double x, delta_x, end_sum, mid_sum, sum1;

    pieces = 1;
    delta_x = (upper - lower)/pieces;
    end_sum = fx(lower) + fx(upper);
    *sum = end_sum*delta_x / 2.0;
    mid_sum = 0.0;
    
    do {
        pieces = pieces*2;
        sum1 = *sum;
        delta_x = (upper - lower)/pieces;
        for (i = 1; i <= pieces/2; i++) {
            x = lower+delta_x*(2.0*i - 1.0);
            mid_sum = mid_sum + fx(x);
        }
        *sum = (end_sum + 2.0*mid_sum)*delta_x*0.5;
    }
    while (fabs(*sum - sum1) > fabs(tol*(*sum)));
}

int main() {
    SAMPLE;
    lower = 1.0;
    upper = 9.0;
    trapez(lower,upper,tol, &sum);
    SAMPLE;
    // printf("area= %.16e\n", sum);
}
