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

//#define ITERATIONS 10000
//#define LOOPSCALE 100

#include "proj_timing.h"

//uint64_t times[LOOPSCALE][ITERATIONS];
void procedure_0 () {
}

int main (int argc, const char * argv[]) {
    int i, j, k;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start, end;

    if (argc != 3){
        printf("usage: loop_ovh loopscale iterations\n");
        return 1;
    }
    int loopscale = atoi((const char *) argv[argc-2]);
    int iterations = atoi((const char *) argv[argc-1]);

    WARMUP(high, low, high1, low1);

    for (j = 0; j < loopscale; j++) {
        for (i = 0; i < iterations; i++) {
            START_COUNT(high, low);

            //measured_loop
            for (k=0; k<j; k++);

            STOP_COUNT(high1, low1);

            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;

            //if (end < start) {
            //    printf("alert! %d at scale %d\n", j, i);
            //} else {
                printf("%d, %llu\n",  j, end-start);
            //}
        }
    }

    return 0;
}
