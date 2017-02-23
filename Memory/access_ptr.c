#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

#include "proj_timing.h"

struct Linklist {
    struct Linklist * next;
};

typedef struct Linklist Linklist;


void memory_access(unsigned long long work_size, int step);

int main (int argc, const char * argv []){
    memory_access(100ul, 1);
    memory_access(32768ul, 1);
    memory_access(65536ul, 1);
    memory_access(131072ul, 1);
    memory_access((1ul) << 30, 1);
    return 0;
}


/*
 * @param work_size array size in terms of integers
 *
 *
 */
void memory_access(unsigned long long work_size, int step) {
    Linklist * linklist;
    int i, tmp;
    Linklist * iter;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;

    if ((linklist = (Linklist *)malloc(work_size * sizeof(Linklist *))) == NULL) {
        exit(EXIT_FAILURE);
    }

    // initialize & cache warmup
    for (i = 0; i < work_size / step - 1; i++) {
        linklist[i * step].next = & linklist[(i + 1) * step];
    }

    linklist[i * step].next = NULL;
    iter = linklist;

    WARMUP(high, low, high1, low1);

    // measurement linklist
    START_COUNT(high, low);
    while (iter != NULL) {
        iter = iter -> next;
    }
    STOP_COUNT(high1, low1);

    start = ((unsigned long long) high << 32) | low;
    end = ((unsigned long long) high1 << 32) | low1;

    printf ("size: %llu\tstep:%d\tlatency:%llu\n", work_size / step * step, step, (end-start) / i);
}
