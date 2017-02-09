#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>

#include "proj_timing.h"

//#define ITERATIONS 10


int main (int argc, const char *argv[]) {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    uint64_t pipebuf;
    int pipefd[2];
    pid_t pid;
    int i;

    WARMUP(high, low, high1, low1);

    int iterations = atoi((const char *) argv[argc-1]);

    for (i = 0; i < iterations; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        START_COUNT(high, low);
        pid = fork();

        if (pid==0){
            //child
            STOP_COUNT(high1, low1);
            end = ((unsigned long long) high1 << 32) | low1;
            write(pipefd[1], &end, sizeof(end));
            close(pipefd[0]);
            close(pipefd[1]);
            //exit(0);
            return 0;
        }else {
            STOP_COUNT(high1, low1);
            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;
            read(pipefd[0], &pipebuf, sizeof(pipebuf));
            end = pipebuf < end ? pipebuf : end;
            close(pipefd[0]);
            close(pipefd[1]);

            printf("%llu\n", end - start);
        }

    }

    return 0;
}
