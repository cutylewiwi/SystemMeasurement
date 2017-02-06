#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "proj_timing.h"

#define ITERATIONS 10

int main () {
    uint64_t start;
    uint64_t end;
    uint32_t low, low1;
    uint32_t high, high1;
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        START_COUNT(low, high);
        STOP_COUNT(low1, high1);

        start = ((uint64_t) high << 32) | low;
        end = ((uint64_t) high1 >> 32) | low1;

        printf("%ll, %ll, %ll\n", start, end, end - start);
    }

    return 0;
}
