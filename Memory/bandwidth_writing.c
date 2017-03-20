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
        #define DOIT(i) manarray[i] = writing;
        #define WRITEINST   \
        do{ \
            writing = rand(); \
            START_COUNT(high, low); \
            DOIT(0) DOIT(64) DOIT(128) DOIT(192) DOIT(256) DOIT(320) DOIT(384) DOIT(448) DOIT(512) DOIT(576)    \
            DOIT(640) DOIT(704) DOIT(768) DOIT(832) DOIT(896) DOIT(960) DOIT(1024) DOIT(1088) DOIT(1152) DOIT(1216)     \
            DOIT(1280) DOIT(1344) DOIT(1408) DOIT(1472) DOIT(1536) DOIT(1600) DOIT(1664) DOIT(1728) DOIT(1792) DOIT(1856)   \
            DOIT(1920) DOIT(1984) DOIT(2048) DOIT(2112) DOIT(2176) DOIT(2240) DOIT(2304) DOIT(2368) DOIT(2432) DOIT(2496)   \
            DOIT(2560) DOIT(2624) DOIT(2688) DOIT(2752) DOIT(2816) DOIT(2880) DOIT(2944) DOIT(3008) DOIT(3072) DOIT(3136)   \
            DOIT(3200) DOIT(3264) DOIT(3328) DOIT(3392) DOIT(3456) DOIT(3520) DOIT(3584) DOIT(3648) DOIT(3712) DOIT(3776)   \
            DOIT(3840) DOIT(3904) DOIT(3968) DOIT(4032) DOIT(4096) DOIT(4160) DOIT(4224) DOIT(4288) DOIT(4352) DOIT(4416)   \
            DOIT(4480) DOIT(4544) DOIT(4608) DOIT(4672) DOIT(4736) DOIT(4800) DOIT(4864) DOIT(4928) DOIT(4992) DOIT(5056)   \
            DOIT(5120) DOIT(5184) DOIT(5248) DOIT(5312) DOIT(5376) DOIT(5440) DOIT(5504) DOIT(5568) DOIT(5632) DOIT(5696)   \
            DOIT(5760) DOIT(5824) DOIT(5888) DOIT(5952) DOIT(6016) DOIT(6080) DOIT(6144) DOIT(6208) DOIT(6272) DOIT(6336)   \
            manarray = &manarray[6400]; \
            STOP_COUNT(high1, low1);    \
            start = ((unsigned long long) high << 32) | low;    \
            end = ((unsigned long long) high1 << 32) | low1;    \
            records[flag++] = end - start;  \
        }while (0);

                flag = 0;
                // HUNDRED(WRITEINST);
                ONE(WRITEINST);

                for (j = 0; j < flag; j++) {
                    printf("write%d:\t %llu\n", i, records[j]);
                }
    }

    free(large_read);
    free(large_write);
    free(l3cache);

    return 0;
}
