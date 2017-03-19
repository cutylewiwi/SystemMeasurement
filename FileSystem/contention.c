#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc.h>
#include <wait.h>

#include "proj_timing.h"

#define FILEPREFIX "contenttestfile"
#define TESTCOUNT 10
#define MAXPROCESS 10

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

void testSeqRead(int fd, int proccount, int printResult){
    long long i;
    uint32_t low, low1, high, high1;
    unsigned long long start, end, totaltime;
    unsigned long long filesize = getFileSize(fd);
    size_t blocksize = getBlockSize(fd);

    WARMUP(high, low, high1, low1);

    char *buf = memalign(blocksize, blocksize);
    if (buf == NULL){
        perror("Buffer allocate error\n");
        exit(1);
    }

    totaltime = 0;
    for (i = 0; i < filesize; i+=blocksize){
        lseek(fd, i, SEEK_SET);
        START_COUNT(high, low);
        if (read(fd, buf, blocksize) != blocksize){
            perror("Read error\n");
        }
        STOP_COUNT(high1, low1);

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;
        totaltime += (end-start);
    }

    free(buf);
    if (printResult)
        printf("%d:\t%f\n", proccount, (double)totaltime/filesize*blocksize);

}

int main(int argc, const char* argv[]){
    int fd, i, j, pcount;
    char filepath[256];
    pid_t pids[MAXPROCESS];

    if (argc != 2){
        perror("Usage: content <test file dir>\n");
    }

    for (pcount = 1; pcount <= MAXPROCESS; ++pcount){

        for (i = 0; i < pcount; ++i){
            if ((pids[i] = fork()) < 0){
                perror("Fork error\n");
                exit(1);
            } else if (pids[i] == 0){
                //test read
                sprintf(filepath, "%s%s%d", argv[1], FILEPREFIX, i); 
                for (j = 0; j < TESTCOUNT; ++j){
                    fd = open(filepath, O_DIRECT);
                    if (fd < 0){
                        perror("File open error\n");
                        exit(1);
                    }
                    testSeqRead(fd, pcount, 1);
                    close(fd);
                } 
                exit(0);
            }else {
                continue;
            }
        }

        //wait child to exit
        int status;
        pid_t pid;
        for (i = 0; i < MAXPROCESS; ++i){
            pid = wait(&status);
        }
    }

    return 0;
}

