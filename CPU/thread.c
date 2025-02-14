#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#include "proj_timing.h"

//#define ITERATIONS 10


uint32_t lowt, hight;
unsigned long long endthread;

void *thread_fn(void *arg){
    STOP_COUNT(hight, lowt);
    endthread = ((unsigned long long) hight << 32) | lowt;
    return NULL;
}

int main (int argc, const char *argv[]) {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    pthread_t td;
    int i;

    WARMUP(high, low, high1, low1);


    int iterations = atoi((const char *) argv[argc-1]);
    //int outer = atoi((const char *) argv[argc-2]);

    //for (j = 0; j < outer; j++){
    for (i = 0; i < iterations; i++) {
        START_COUNT(high, low);
        pthread_create(&td, NULL, thread_fn, NULL);
        STOP_COUNT(high1, low1);

        pthread_join(td, NULL);
        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;


        end = endthread < end ? endthread : end;

        //printf("%d, %llu\n", j, end - start);
        printf("%llu\n", end - start);
    }
    //}

    return 0;
}
