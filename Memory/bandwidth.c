#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>

#include "proj_timing.h"
#define ONE(m)      m
#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)
#define FIVEHUN(m)  HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m)
#define THOUSAND(m) FIVEHUN(m) FIVEHUN(m)
#define ITERATIONS  300
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
    unsigned long long * ptr;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;
    unsigned int * manarray;
    unsigned int sum;
    volatile unsigned int store;
    unsigned int writing;
    volatile unsigned int * ptrStore;

    srand((unsigned)time(NULL));

    large_read = (unsigned char *) malloc(CHUNKS * CACHE);
    large_write = (unsigned char *) malloc(CHUNKS * CACHE);
    l3cache = (unsigned char *) malloc(CACHE);

    for (i = 0; i < CHUNKS * CACHE / sizeof(unsigned char); i++) {
        large_read[i] = (unsigned char) rand() % 255;
    }

    for (i = 0; i < CHUNKS * CACHE / sizeof(unsigned char); i++) {
        large_write[i] = (unsigned char) rand() % 255;
    }

    WARMUP(high, low, high1, low1);
    manarray = (unsigned int *) large_read;
    for (i = 0; i <  ITERATIONS; i++) {

#define READINST \
do {    \
    START_COUNT(high, low); \
    sum += manarray[0] + manarray[64] + manarray[128] + manarray[192] + manarray[256] + manarray[320] + manarray[384] + manarray[448] + manarray[512] + manarray[576] + \
           manarray[640] + manarray[704] + manarray[768] + manarray[832] + manarray[896] + manarray[960] + manarray[1024] + manarray[1088] + manarray[1152] + manarray[1216] + \
           manarray[1280] + manarray[1344] + manarray[1408] + manarray[1472] + manarray[1536] + manarray[1600] + manarray[1664] + manarray[1728] + manarray[1792] + manarray[1856] + \
           manarray[1920] + manarray[1984] + manarray[2048] + manarray[2112] + manarray[2176] + manarray[2240] + manarray[2304] + manarray[2368] + manarray[2432] + manarray[2496] + \
           manarray[2560] + manarray[2624] + manarray[2688] + manarray[2752] + manarray[2816] + manarray[2880] + manarray[2944] + manarray[3008] + manarray[3072] + manarray[3136] + \
           manarray[3200] + manarray[3264] + manarray[3328] + manarray[3392] + manarray[3456] + manarray[3520] + manarray[3584] + manarray[3648] + manarray[3712] + manarray[3776] + \
           manarray[3840] + manarray[3904] + manarray[3968] + manarray[4032] + manarray[4096] + manarray[4160] + manarray[4224] + manarray[4288] + manarray[4352] + manarray[4416] + \
           manarray[4480] + manarray[4544] + manarray[4608] + manarray[4672] + manarray[4736] + manarray[4800] + manarray[4864] + manarray[4928] + manarray[4992] + manarray[5056] + \
           manarray[5120] + manarray[5184] + manarray[5248] + manarray[5312] + manarray[5376] + manarray[5440] + manarray[5504] + manarray[5568] + manarray[5632] + manarray[5696] + \
           manarray[5760] + manarray[5824] + manarray[5888] + manarray[5952] + manarray[6016] + manarray[6080] + manarray[6144] + manarray[6208] + manarray[6272] + manarray[6336] ; \
    manarray = &manarray[6400]; \
    STOP_COUNT(high1, low1);    \
    store = sum; \
    start = ((unsigned long long) high << 32) | low;    \
    end = ((unsigned long long) high1 << 32) | low1;    \
    records[flag++] = end - start;  \
}while(0);
        flag = 0;
        // HUNDRED(READINST);
        ONE(READINST);

        for (j = 0; j < flag; j++) {
            printf("read%d:\t %llu\n", i, records[j]);
        }

    }

    free(large_read);
    free(large_write);
    free(l3cache);

    return 0;
}
