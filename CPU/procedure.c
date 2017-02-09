#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>



#define ITERATIONS 10

#include "proj_timing.h"

static uint32_t low, low1;
static uint32_t high, high1;
static uint64_t start, end;

int arguments[ITERATIONS][7];

void procedure_0 () {
    return;
}

void procedure_1 (int arg1) {
}

void procedure_2 (int arg1, int arg2) {
}

void procedure_3 (int arg1, int arg2, int arg3) {
}

void procedure_4 (int arg1, int arg2, int arg3, int arg4) {
}

void procedure_5 (int arg1, int arg2, int arg3, int arg4, int arg5) {
}

void procedure_6 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
}

void procedure_7 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
}

#define output(para_count)\
do{\
    STOP_COUNT(high1, low1);\
    start = ((unsigned long long) high << 32) | low;\
    end = ((unsigned long long) high1 << 32) | low1;\
    printf ("%d, %" PRIu64 "\n", para_count, end-start);\
}while(0)

int main (int argc, const char * argv[]){
    int i, j;

    if (argc != 3) {
        printf("usage: procedure outerloop innerloop\n");
        return 1;
    }

    int outer = atoi((const char *) argv[argc-2]);
    int inner = atoi((const char *) argv[argc-1]);

    WARMUP(high, low, high1, low1);
    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
        }
        output(-1);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_0();
        }
        output(0);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_1(1);
        }
        output(1);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_2(1, 2);
        }
        output(2);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_3(1, 2, 3);
        }
        output(3);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_4(1, 2, 3, 4);
        }
        output(4);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_5(1, 2, 3, 4, 5);
        }
        output(5);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_6(1, 2, 3, 4, 5, 6);
        }
        output(6);
    }

    for (i = 0; i < outer; i++) {
        START_COUNT(high, low);
        for (j=0; j < inner; j++){
            procedure_7(1, 2, 3, 4, 5, 6, 7);
        }
        output(7);
    }

    return 0;
}
