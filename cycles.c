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
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        START_COUNT(low, high);
        sleep(10);
        STOP_COUNT(low1, high1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;

        // printf("%llu\t%llu\t%llu\n", start, end, end - start);
        if (end < start) {
            printf("alert! %d\n", i);
        }
        records[i] = end - start;
    }

    return 0;
}
