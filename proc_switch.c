#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>

#include "proj_timing.h"

#define ITERATIONS 10


int main (int argc, const char *argv[]) {
    int pipefd[2];
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    pid_t pid;
    int i;
    char buf[1];

    WARMUP(high, low, high1, low1);

    int iterations = atoi((const char *) argv[argc-1]);
    for (i = 0; i < iterations; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid==0){
            //child
            read(pipefd[0], buf, 1);
            STOP_COUNT(high1, low1);
            end = ((unsigned long long) high1 << 32) | low1;
            write(pipefd[1], &end, sizeof(end));
            close(pipefd[0]);
            close(pipefd[1]);
            exit(0);
        }else {
            // wait for children to reach read block
            // sleep(1);
            START_COUNT(high, low);
            write(pipefd[1], buf, 1);
            wait(NULL);
            start = ((unsigned long long) high << 32) | low;
            read(pipefd[0], &end, sizeof(end));
            close(pipefd[0]);
            close(pipefd[1]);
            printf("%llu\n", end - start);
            fflush(stdout);
        }

    }

    return 0;
}
