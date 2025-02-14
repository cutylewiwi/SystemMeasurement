#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "proj_timing.h"

#define FILEPATH "filecache.tmp"
#define TESTCOUNT 10
#define MAXFILESIZE 1UL << 33
#define MINFILESIZE 1UL << 27

void clearFile(char *filepath){
    FILE *fp = fopen(filepath, "w");
    fclose(fp);
}

void createFile(unsigned long long filesize, char *filepath){
    long long i;
    FILE *fp = fopen(filepath, "a");
    for (i = ftell(fp); i < filesize; i++) {
        fputc(rand() % 128,fp);
    }

    if (ftell(fp) != filesize){
        perror("Create file error\n");
        exit(1);
    }
    if (fflush(fp) != 0){
        perror("Create file error\n");
        exit(1);
    }
    fclose(fp);
}

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

void testRead(int fd, unsigned long long filesize, int printResult){
    long long i;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;
    unsigned long long totaltime;
    WARMUP(high, low, high1, low1);
    srand((unsigned) time(NULL));
    totaltime = 0;
    size_t blocksize = getBlockSize(fd);
    char *buf = malloc(blocksize);

    for (i = 0; i < filesize; i+=blocksize){
        lseek(fd, i, SEEK_SET);
        START_COUNT(high, low);
        if (read(fd, buf, blocksize) != blocksize){
            perror("Read error\n");
            exit(1);
        }
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;
        totaltime += (end-start);
    }
    free(buf);

    if (printResult)
        printf("%llu:\t%f\n", filesize, (double)totaltime/filesize*blocksize);
    
}

int main(){
    unsigned long long i, filesize, step;
    int fd;

    clearFile(FILEPATH);
    for (filesize = MINFILESIZE; filesize <= MAXFILESIZE; filesize+=MINFILESIZE){
        createFile(filesize, FILEPATH);
        
        fd = open(FILEPATH, O_RDONLY);
        if (fd < 0){
            perror("File open error\n");
            exit(1);
        }
        if (getFileSize(fd) != filesize){
            perror("Wrong test file size\n");
            exit(1);
        }
        for (i = 0; i < TESTCOUNT; ++i){
            testRead(fd, filesize, 1);
        }

        close(fd);
    }

    return 0;
}

