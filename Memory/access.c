#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>

#include "proj_timing.h"

void memory_access(unsigned long long work_size, int step);

int main (int argc, const char * argv []){
    memory_access(10000ul, 2);
    memory_access(32768ul, 2);
    memory_access(65536ul, 2);
    memory_access((1ul) << 30, 2);
    return 0;
}


/*
 * @param work_size array size in terms of integers
 *
 *
 */
void memory_access(unsigned long long work_size, int step) {
    volatile int * workload;
    int i, tmp;
    int * iter;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;
    time_t t;

    srand((unsigned) time(&t));

    if ((workload = (int *)malloc(work_size * sizeof(int *))) == NULL) {
        exit(EXIT_FAILURE);
    }

    // initialize & cache warmup
    for (i = 0; i < work_size / step; i++) {
        workload[i * step] = rand();
    }

    WARMUP(high, low, high1, low1);

    // measurement workload
    START_COUNT(high, low);
    for (i = 0, iter = & tmp; i < work_size / step; i++) {
        *iter = workload[i * step]+i;
    }
    STOP_COUNT(high1, low1);

    start = ((unsigned long long) high << 32) | low;
    end = ((unsigned long long) high1 << 32) | low1;

    printf ("size: %llu\tstep:%d\tlatency:%llu\n", work_size / step * step, step, (end-start) / i);
}
