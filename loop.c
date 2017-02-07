#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include <unistd.h>

#define ITERATIONS 10
#define LOOPSCALE 1000

#include "proj_timing.h"

double records[LOOPSCALE];
unsigned long long cycles[ITERATIONS];

int main (int argc, const char * argv[]) {
    int i, j, k;
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long sum;

    int loop = atoi((const char *) argv[argc-1]);


    // i: loop scale increasing
    //for (i = 0; i < LOOPSCALE; i++) {
        // j: multile iterations
        records[loop-1] = 0;
        for (j = 0; j < ITERATIONS; j++) {
            START_COUNT(high, low);

            // k: loop itself
            asm volatile ("mov    %0, %%eax\n\t"
                          "jmp    end\n\t"
                          "begin:\n\t"
                          "sub    $0x1,%%eax\n\t"
                          "end:\n\t"
                          "test   %%eax,%%eax\n\t"
                          "jns    begin\n\t"
                          :: "r"(loop):"%rax");

            STOP_COUNT(high1, low1);

            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;

            if (end < start) {
                printf("alert! %d at scale %d\n", j, i);
            }
            records[loop-1] += end - start;
        }

        records[loop-1] /= 10; // mean
        records[loop-1] /= loop+1;  // mean for each loop round
    //}


    //for (i = 0; i < loop; i++) {
        printf ("loop at scale %d cost %.2lf cycles\n", loop, records[loop-1]);
    //}
    return 0;
}
