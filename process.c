#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>

#include "proj_timing.h"

#define ITERATIONS 10


int main () {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    pid_t pid;
    int i;

    WARMUP(high, low, high1, low1);

    for (i = 0; i < ITERATIONS; i++) {
        START_COUNT(high, low);
        pid = fork();

        if (pid==0){
            //child
            break; 
        }else {
            STOP_COUNT(high1, low1);
            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;
            wait(NULL);
            printf("%llu\n", end - start);
        }

    }

    return 0;
}
