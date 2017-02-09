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
    pthread_exit(NULL);
}

int main (int argc, const char *argv[]) {
    unsigned long long start;
    uint32_t high, low;
    pthread_t td;
    int i;

    WARMUP(high, low, hight, lowt);
    
    int iterations = atoi((const char *) argv[argc-1]);
    for (i = 0; i < iterations; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pthread_create(&td, NULL, thread_fn, NULL);

        START_COUNT(high, low);
        write(pipefd[1], buf, 1);

        pthread_join(td, NULL);
        close(pipefd[0]);
        close(pipefd[1]);
        start = ((unsigned long long) high << 32) | low;
        endthread = ((unsigned long long) hight << 32) | lowt;


        // end = endthread < end ? endthread : end;

        printf("%llu\n", endthread - start);
        fflush(stdout);
    }

    return 0;
}
