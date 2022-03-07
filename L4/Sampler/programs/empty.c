#include "sampler.h"

int
main(int argc, char **argv)
{
    sampler_init(&argc, argv);

    SAMPLE;
    SAMPLE;

    return 0;
}
