#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <malloc.h>

#include "proj_timing.h"

#define FILEPREFIX "testfile"
#define TESTCOUNT 10
#define MAXFILESIZE 1UL << 30
#define MINFILESIZE 1UL << 20

size_t getBlockSize(int fd){
    struct stat buf;
    fstat(fd, &buf);
    return buf.st_blksize;
}

size_t getFileSize(int fd){
    struct stat buf;
    fstat(fd, &buf);
    return buf.st_size;
}

void testRandRead(int fd, unsigned long long filesize, int printResult){
    long long i, samplenum, offset;
    uint32_t low, low1, high, high1;
    unsigned long long start, end, totaltime;
    WARMUP(high, low, high1, low1);

    totaltime = 0;
    size_t blocksize = getBlockSize(fd);
    char *buf = memalign(blocksize, blocksize);
    if (buf == NULL){
        perror("Buffer allocate error\n");
    }

    //printf("blocksize %lu\n", blocksize);
    samplenum = filesize/blocksize;
    for (i = 0; i < samplenum; ++i){
        offset = blocksize*rand()%samplenum;
        lseek(fd, offset, SEEK_SET);

        START_COUNT(high, low);
        if (read(fd, buf, blocksize)<0){
            perror("Read error\n");
        }
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;
        totaltime += (end-start);
    }

    free(buf);
    if (printResult)
        printf("%llu:\t%f\n", filesize, (double)totaltime/(double)filesize*blocksize);
    
}

int main(int argc, const char* argv[]){
    unsigned long long i, filesize, step;
    int fd;
    char filepath[256];
    srand(time(NULL));

    if (argc != 2){
        perror("Usage: randread <test file dir>\n");
    }
    
    for (filesize = MINFILESIZE; filesize < MAXFILESIZE; filesize<<=1){
        
        sprintf(filepath, "%s%s%llu", argv[1], FILEPREFIX, filesize); 
        for (i = 0; i < TESTCOUNT; ++i){
            fd = open(filepath, O_DIRECT);
            if (fd < 0){
                perror("File open error\n");
            }
            if (getFileSize(fd) != filesize){
                perror("Wrong test file size\n");
            }
            testRandRead(fd, filesize, 1);
            close(fd);
        }
    }

    return 0;
}

