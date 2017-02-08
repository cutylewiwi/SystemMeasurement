#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#include "proj_timing.h"

#define ITERATIONS 100


uint32_t lowt, hight;
unsigned long long endthread;
int pipefd[2];
char buf[1];

void *thread_fn(void *arg){
    // blocking the thread by read
    read(pipefd[0], buf, 1);
    STOP_COUNT(hight, lowt);
}

int main () {
    unsigned long long start;
    unsigned long long end;
    uint32_t high, low;
    pthread_t td;
    int i;

    WARMUP(high, low, hight, lowt);
    for (i = 0; i < ITERATIONS; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pthread_create(&td, NULL, thread_fn, NULL);

        sleep(1);
        write(pipefd[1], buf, 1);
        START_COUNT(high, low);

        pthread_join(td, NULL);
        start = ((unsigned long long) high << 32) | low;
        endthread = ((unsigned long long) hight << 32) | lowt;


        // end = endthread < end ? endthread : end;

        printf("%llu\n", endthread - start);
    }

    return 0;
}
