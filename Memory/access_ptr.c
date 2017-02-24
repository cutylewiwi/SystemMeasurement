#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>

#include "proj_timing.h"

#define ITERATIONS 1000

struct Linklist {
    struct Linklist * next;
};

typedef struct Linklist Linklist;


void memory_access(unsigned long long work_size, int stride);
void cache_measure(int stride);

int main (int argc, const char * argv []){
    cache_measure(16);
    cache_measure(32);
    cache_measure(64);
    cache_measure(128);
    cache_measure(256);
    return 0;
}

void cache_measure(int stride) {
    memory_access(1ul << 10, stride);  // 1K
    memory_access(1ul << 11, stride);  // 2K
    memory_access(1ul << 12, stride);  // 4K
    memory_access(1ul << 13, stride);  // 8K
    memory_access(1ul << 14, stride);  // 16K
    memory_access(1ul << 15, stride);  // 32K
    memory_access(1ul << 16, stride);  // 64K
    memory_access(1ul << 17, stride);  // 128K
    memory_access(1ul << 18, stride);  // 256K
    memory_access(1ul << 19, stride);  // 512K
    memory_access(1ul << 20, stride);  // 1M
    memory_access(1ul << 21, stride);  // 2M
    memory_access(1ul << 22, stride);  // 4M
    memory_access(1ul << 23, stride);  // 8M
    memory_access(1ul << 24, stride);  // 16M
    printf ("\n");
}


/*
 * @param work_size array size in terms of integers
 *
 *
 */
void memory_access(unsigned long long work_size, int stride) {
    Linklist * linklist;
    int i, step;
    Linklist * iter;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;
    time_t t;

    srand((unsigned) time(&t));

    if ((linklist = (Linklist *)malloc(work_size * sizeof(Linklist *))) == NULL) {
        exit(EXIT_FAILURE);
    }

    // initialize & cache warmup
    step = ITERATIONS;
    iter = linklist;
    for (i = 0; i < work_size; i++) {
        linklist[i].next = NULL;
    }

    for (i = 0; i < work_size; i++) {
        linklist[i].next = &linklist[((i / stride + 1) * stride + rand() % stride) % stride];
    }

    WARMUP(high, low, high1, low1);

    // measurement linklist
    START_COUNT(high, low);
    // while (step --> 0) {
#define ONE \
        iter = iter -> next;
#define TEN     ONE ONE ONE ONE ONE ONE ONE ONE ONE ONE
#define HANDRED TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN
        HANDRED
    // }
    STOP_COUNT(high1, low1);

    start = ((unsigned long long) high << 32) | low;
    end = ((unsigned long long) high1 << 32) | low1;

    free(linklist);

    printf ("workload size: %lluKB\tstride:%d\tlatency:%llu\n", work_size / 1024, stride, (end-start) / (100));
}
