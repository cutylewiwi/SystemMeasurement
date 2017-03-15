#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "proj_timing.h"

#define FILEPATH "/tmp/filecache.tmp"
#define SAMPLENUM 100
#define MAXFILESIZE 1UL << 34
#define MINFILESIZE 1UL << 23
void createFile(unsigned long long filesize, char *filepath){
    FILE *fp = fopen(filepath, "w");
    fseek(fp, filesize, SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}

int main(){
    char c;
    unsigned long long i, filesize, step;
    FILE *fp;
    uint32_t low, low1;
    uint32_t high, high1;
    unsigned long long start;
    unsigned long long end;

    WARMUP(high, low, high1, low1);
    for (filesize = MINFILESIZE; filesize < MAXFILESIZE; filesize+=MINFILESIZE){
        createFile(filesize, FILEPATH);
        
        fp = fopen(FILEPATH, "r");
        step = filesize / SAMPLENUM;
        for (i = 0; i < filesize; i+=step){
            fseek(fp, i, SEEK_SET);
            START_COUNT(high, low);
            //c = getc(fp);
            fgets(&c, 1, fp);
            STOP_COUNT(high1, low1);

            start = ((unsigned long long) high << 32) | low;
            end = ((unsigned long long) high1 << 32) | low1;
            printf("%llu:\t%llu\n", filesize, end-start);
        }
        fclose(fp);
    }

    return 0;
}

