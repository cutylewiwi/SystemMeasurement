#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>

#include "proj_timing.h"

// TODO: random permutation stride

#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)
#define FIVEHUN(m)  HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m)
#define THOUSAND(m) FIVEHUN(m) FIVEHUN(m)
#define ITERATIONS  3
#define CHUNKS      32
#define MEGA        (1 << 20)
#define CACHE       (8 * MEGA)

unsigned long long records[1000];


int main (int argc, const char * argv[]) {
    int i, j, flag;
    unsigned int random_index[6];
    unsigned char * large_read;
    unsigned char * large_write;
    unsigned char * l3cache;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;

    srand((unsigned)time(NULL));

    large_read = (unsigned char *) malloc(CHUNKS * CACHE);
    large_write = (unsigned char *) malloc(CHUNKS * CACHE);
    l3cache = (unsigned char *) malloc(CACHE);

    for (i = 0; i < CHUNKS * CACHE / sizeof(unsigned char); i++) {
        large_read[i] = (unsigned char) rand() % 255;
        large_write[i] = (unsigned char) rand() % 255;
    }

    for (i = 0; i < 6; i++) {
        flag = 1;
        random_index[i] = rand() % CHUNKS;
        while (flag) {
            flag = 0;
            for (j = i-1; j >= 0; j--) {
                if (random_index[i] == random_index[j]) {
                    flag = 1;
                    random_index[i] = rand() % CHUNKS;
                    break;
                }
            }
        }
    }

    WARMUP(high, low, high1, low1);

    for (i = 0; i <  ITERATIONS; i++) {
#define READINST \
do {    \
    START_COUNT(high, low); \
    memcpy(l3cache, &large_read[random_index[i] * CACHE], CACHE);   \
    STOP_COUNT(high1, low1);    \
    start = ((unsigned long long) high << 32) | low;    \
    end = ((unsigned long long) high1 << 32) | low1;    \
    records[flag++] = end - start;  \
}while(0);
        flag = 0;
        HUNDRED(READINST);

        for (j = 0; j < flag; j++) {
            printf("read%d%02d:\t %llu\n", i, j, records[j]);
        }

#define WRITEINST   \
do{ \
    START_COUNT(high, low); \
    memcpy(&large_write[random_index[i + 3] * CACHE], l3cache, CACHE);   \
    STOP_COUNT(high1, low1);    \
    start = ((unsigned long long) high << 32) | low;    \
    end = ((unsigned long long) high1 << 32) | low1;    \
    records[flag++] = end - start;  \
}while (0);

        flag = 0;
        HUNDRED(WRITEINST);

        for (j = 0; j < flag; j++) {
            printf("write%d%02d:\t %llu\n", i, j, records[j]);
        }

    }

    free(large_read);
    free(large_write);
    free(l3cache);

    return 0;
}
