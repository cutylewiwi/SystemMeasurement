#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>



#define ITERATIONS 10

#include "proj_timing.h"

static int flag = 0;
static unsigned long long records[ITERATIONS];
static uint32_t low, low1;
static uint32_t high, high1;

int arguments[ITERATIONS][7];

void procedure_0 () {
    STOP_COUNT(high1, low1);
}

void procedure_1 (int arg1) {
    STOP_COUNT(high1, low1);
}

void procedure_2 (int arg1, int arg2) {
    STOP_COUNT(high1, low1);
}

void procedure_3 (int arg1, int arg2, int arg3) {
    STOP_COUNT(high1, low1);
}

void procedure_4 (int arg1, int arg2, int arg3, int arg4) {
    STOP_COUNT(high1, low1);
}

void procedure_5 (int arg1, int arg2, int arg3, int arg4, int arg5) {
    STOP_COUNT(high1, low1);
}

void procedure_6 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    STOP_COUNT(high1, low1);
}

void procedure_7 (int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    STOP_COUNT(high1, low1);
}

int main (int argc, const char * argv[]){
    int i;
    int procedure_flag;
    unsigned long long start;
    unsigned long long end;
    unsigned long long sum;

    procedure_flag = atoi ((const char *) argv[argc-1]);
    sum = 0;
    for (i = 0; i < ITERATIONS; i++) {

        switch (procedure_flag) {
            case 0:
            START_COUNT(high, low);
            procedure_0();
            break;

            case 1:
            START_COUNT(high, low);
            procedure_1(arguments[i][0]);
            break;

            case 2:
            START_COUNT(high, low);
            procedure_2(arguments[i][0], arguments[i][1]);
            break;

            case 3:
            START_COUNT(high, low);
            procedure_3(arguments[i][0], arguments[i][1], arguments[i][2]);
            break;

            case 4:
            START_COUNT(high, low);
            procedure_4(arguments[i][0], arguments[i][1], arguments[i][2], arguments[i][3]);
            break;

            case 5:
            START_COUNT(high, low);
            procedure_5(arguments[i][0], arguments[i][1], arguments[i][2], arguments[i][3], arguments[i][4]);
            break;

            case 6:
            START_COUNT(high, low);
            procedure_6(arguments[i][0], arguments[i][1], arguments[i][2], arguments[i][3], arguments[i][4], arguments[i][5]);
            break;

            case 7:
            START_COUNT(high, low);
            procedure_7(arguments[i][0], arguments[i][1], arguments[i][2], arguments[i][3], arguments[i][4], arguments[i][5], arguments[i][6]);
            break;

            default:
            break;
        }

        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) high1 << 32) | low1;
        records[i] = end - start;
        sum += records[i];
        printf ("%llu\n", records[i]);
    }


    printf ("procedure call with %d arguments cost %.5lf cycles\n", procedure_flag, (double)sum / ITERATIONS);

    return 0;
}
