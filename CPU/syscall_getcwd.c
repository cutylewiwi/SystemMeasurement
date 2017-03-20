#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

#include "proj_timing.h"

#define ITERATIONS 10

int main (int argc, const char * argv[]) {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    int i;
    char cwd[1024];

    int iterations = atoi((const char *) argv[argc-1]);
    WARMUP(high, low, high1, low1);

    for (i = 0; i < iterations; i++) {
        START_COUNT(high, low);
        getcwd(cwd, sizeof(cwd));
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;

        printf("%llu\n", end - start);
    }

    return 0;
}
