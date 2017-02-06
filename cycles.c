#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include <unistd.h>

#define ITERATIONS 10

#include "proj_timing.h"

unsigned long long records[ITERATIONS];

int main (int argc, const char * arg[]){
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long sum;
    int i;

    for (i = 0; i < ITERATIONS; i++) {
        START_COUNT(high, low);
        sleep(10);
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;

        // printf("%llu\t%llu\t%llu\n", start, end, end - start);
        if (end < start) {
            printf("alert! %d\n", i);
        }
        records[i] = end - start;
    }

    sum = ;
    for (i = 0; i < ITERATIONS; i++) {
        printf("cycles sample %d: %llu\n", i, records[i]);

        // As CPU frequency will be at the scale of 1GHZ -> 10 ^ 9 ~ 10 ^ 10
        // unsigned long long will be save from overflow
        sum += records[i];
    }

    printf ("samples: %d\n", ITERATIONS);

    // Under the scale of sum
    // cast from unsigned longlong to double will be safe
    printf ("mean: %lf\n", (double)sum / 10);
    printf ("frequency: %.3lf\n", (double)sum / 1e10);

    return 0;
}
