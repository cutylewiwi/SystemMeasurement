/*
 *  statistics.c
 *  calculate mean and standard deviation for os project
 *  author: Yudong Wu (cutylewiwi)
 *
 */

#include <math.h>
#include <stdlib.h>
#include <memory.h>

 // be careful: overflow and precision lose might happpppen!
double proj_mean (unsigned long long * input_vector, int num) {
    int i;
    double sum;

    sum = 0;
    for (i = 0; i < num; i++) {
        sum += input_vector[i];
    }

    return sum / num;
}

double proj_sd (unsigned long long * input_vector, int num) {
    int i;
    double mean;
    double ret;
    double * input;

    input = (double *)malloc(sizeof(double) * num);
    memset(input, 0, sizeof(input));

    for (i = 0; i < num; i++) {
        mean += input_vector[i];
        input[i] = input_vector[i];
    }

    mean /= 10;
    ret = 0;
    for (i = 0; i < num; i++) {
        input[i] -= mean;
        ret += input[i] * input[i];
    }

    ret /= 10;
    return sqrt(ret);
}
