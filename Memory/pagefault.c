#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "proj_timing.h"

#define	FIVE(m)		m m m m m
#define	TEN(m)		FIVE(m) FIVE(m)
#define	FIFTY(m)	TEN(m) TEN(m) TEN(m) TEN(m) TEN(m)
#define	HUNDRED(m)	FIFTY(m) FIFTY(m)
#define FIVEHUN(m)  HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m) HUNDRED(m)
#define THOUSAND(m) FIVEHUN(m) FIVEHUN(m)
#define ITERATIONS  3
#define CHUNKS      3000
#define PAGE        (1 << 12)       // page size
#define STRIDE      60

#define FILEPATH    "/tmp/pagefaultmmap.tmp"
#define FILESIZE    (CHUNKS * PAGE)

unsigned long long records[CHUNKS/STRIDE];

int main (int argc, const char * argv[]){
    int i, j, flag;
    int fd;
    int result;
    unsigned char * map;
    unsigned index[CHUNKS/STRIDE];
    volatile char buf;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;

    srand((unsigned)time(NULL));

    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    result = lseek(fd, FILESIZE-1, SEEK_SET);
    if (result == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    result = write(fd, "", 1);
    if (result != 1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    map = (unsigned char *) mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < CHUNKS/STRIDE; j++) {
        index[j] = rand() % PAGE + (j * STRIDE + rand() % STRIDE) * PAGE;
    }

    WARMUP(high, low, high1, low1);

    flag = 0;
    for (j = 0; j < CHUNKS / STRIDE; j++) {
        START_COUNT(high, low);
        buf = map[index[j]];
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;

        records[flag++] = end - start;
    }


    for (j = 0; j < CHUNKS / STRIDE; j++) {
        printf("map%d:\t%llu\n", j, records[j]);
    }

    if (munmap(map, FILESIZE) == -1) {
        perror("Error un-mmapping the file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}
