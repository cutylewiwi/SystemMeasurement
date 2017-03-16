#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "proj_timing.h"

#define FILEPATH "/tmp/filecache.tmp"
#define SAMPLENUM 100
#define TESTCOUNT 1
#define MAXFILESIZE 1UL << 33
#define MINFILESIZE 1UL << 23
#define BLOCKSIZE 1UL << 12

unsigned long long result [SAMPLENUM];

void createFile(unsigned long long filesize, char *filepath){
    FILE *fp = fopen(filepath, "w");
    fseek(fp, filesize, SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}


void testRead(int fd, unsigned long long filesize, int printResult){
    char buf[2];
    long long i;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;
    unsigned long long totaltime;
    WARMUP(high, low, high1, low1);
    totaltime = 0;
    for (i = 0; i < filesize; i+=BLOCKSIZE){
        lseek(fd, i, SEEK_SET);
        START_COUNT(high, low);
        //c = getc(fp);
        //fgets(&c, 1, fp);
        read(fd, buf, 1);
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;
        totaltime += (end-start);
    }
    if (printResult)
        printf("%llu:\t%llu\n", filesize, totaltime);
    
}

int main(){
    unsigned long long i, filesize, step;
    int fd;

    for (filesize = MINFILESIZE; filesize < MAXFILESIZE; filesize+=MINFILESIZE){
        createFile(filesize, FILEPATH);
        
        fd = open(FILEPATH, O_RDONLY);
        
        testRead(fd, filesize, 0);
        for (i = 0; i < TESTCOUNT; ++i){
            testRead(fd, filesize, 1);
        }

        close(fd);
    }

    return 0;
}

