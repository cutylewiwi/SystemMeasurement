#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "proj_timing.h"

#define ITERATIONS 10

int main () {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        START_COUNT(low, high);
        STOP_COUNT(low1, high1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 >> 32) | low1;

        printf("%llu, %llu, %llu\n", start, end, end - start);
    }

    return 0;
}
