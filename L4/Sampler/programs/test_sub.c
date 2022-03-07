#include "sampler.h"

#ifndef SIZE
#define SIZE 10000
#endif

void TestLoop(int nTimes)
{
    static int TestDim[SIZE];
    int tmp;
    int iLoop;

    while (nTimes > 0) {
        --nTimes;

        iLoop = SIZE;
        while (iLoop > 0) {
            --iLoop;
            tmp = TestDim[0];
            TestDim[0] = TestDim[nTimes];
            TestDim[nTimes] = tmp;
        }
    }
}

int main(int argc, char **argv)
{
    sampler_init(&argc, argv);

    SAMPLE;
    TestLoop(SIZE / 10);
    SAMPLE;
    TestLoop(SIZE / 5);
    SAMPLE;
    TestLoop(SIZE / 2);
    SAMPLE;
    TestLoop(SIZE / 1);
    SAMPLE;
}
