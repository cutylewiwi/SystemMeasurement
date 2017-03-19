#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILEPATH "testfile"
#define TESTCOUNT 2
#define MAXFILESIZE 1UL << 32
#define MINFILESIZE 1UL << 12
//#define MINFILESIZE 1UL << 26


void createFile(unsigned long long filesize, char *filepath){
    long long i;
    FILE *fp = fopen(filepath, "w");
    for (i = 0; i < filesize; i++) {
        fputc(rand() % 128,fp);
    }
    
    if (ftell(fp) != filesize){
        perror("Create file error\n");
    }
    fclose(fp);
}

int main(){
    unsigned long long filesize, step;
    int fd;
    char filepath[256];

    for (filesize = MINFILESIZE; filesize < MAXFILESIZE; filesize<<=1){
        sprintf(filepath, "%s%llu", FILEPATH, filesize); 
        createFile(filesize, filepath);
    }

    return 0;
}

