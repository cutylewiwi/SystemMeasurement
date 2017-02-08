/**
 * Measure the overhead of using a loop to measure many iterations of an operation
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

#include <unistd.h>

#define ITERATIONS 100
#define LOOPSCALE 10

#include "proj_timing.h"

uint64_t times[LOOPSCALE][ITERATIONS];

static void inline measured_loop(unsigned int n)
{
    int k;
    for (k=0; k<n; k++);
}

int main (int argc, const char * argv[]) {
    int i, j, k;
    uint32_t low, low1;
    uint32_t high, high1;
    uint32_t start, end;

    WARMUP(high, low, high1, low1);

    for (j = 0; j < LOOPSCALE; j++) {
        for (i = 0; i < ITERATIONS; i++) {
            START_COUNT(high, low);

            measured_loop(j);

            STOP_COUNT(high1, low1);

            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;

            if (end < start) {
                printf("alert! %d at scale %d\n", j, i);
                times[j][i] = 0;
            } else {
                times[j][i] = end - start;
            }
        }
    }

    for (j=0; j<LOOPSCALE; j++){
        printf("loopscale: %d\n", j);
        for (i=0; i<ITERATIONS; i++){
            printf("%ld\n", times[j][i]); 
        }

    }

    return 0;
}
