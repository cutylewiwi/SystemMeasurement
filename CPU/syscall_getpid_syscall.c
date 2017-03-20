#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

#include "proj_timing.h"

#define ITERATIONS 10

#define __NR_getpid 39
// pid_t my_getpid()
// {
//     pid_t ret;
//     asm volatile
//     (
//         "syscall"
//         : "=a" (ret)
//         : "0"(__NR_getpid)
//         : "cc", "rcx", "r11", "memory"
//     );
//     return ret;
// }

int main (int argc, const char * argv[]) {
    unsigned long long start;
    unsigned long long end;
    uint32_t low, low1;
    uint32_t high, high1;
    int i;
    pid_t pid;
    volatile pid_t pid1;

    int iterations = atoi((const char *) argv[argc-1]);
    WARMUP(high, low, high1, low1);

    for (i = 0; i < iterations; i++) {
        START_COUNT(high, low);

        asm volatile
        (
            "syscall"
            : "=a" (pid)
            : "0"(__NR_getpid)
            : "cc", "rcx", "r11", "memory"
        );
        STOP_COUNT(high1, low1);
        pid1 = pid;

        // printf("pid: %d\n", pid1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;

        printf("%llu\n", end - start);
    }

    return 0;
}
