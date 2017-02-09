#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>

#include "proj_timing.h"

#define ITERATIONS 10


int enter;
uint32_t high, low;
uint32_t lowt, hight;
unsigned long long start;
unsigned long long end;
pthread_mutex_t mutex;
pthread_cond_t cond_start;
pthread_cond_t cond_wait;

void *thread_fn(void *arg){
    pthread_mutex_lock(&mutex);
    enter = 1;
    pthread_cond_wait(&cond_wait, &mutex); 
    STOP_COUNT(hight, lowt);
    pthread_mutex_unlock(&mutex);
}

int main (int argc, const char *argv[]) {
    unsigned long long start;
    uint32_t high, low;
    pthread_t td;
    int i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_wait, NULL);

    WARMUP(high, low, hight, lowt);
    
    int iterations = atoi((const char *) argv[argc-1]);
    for (i = 0; i < iterations; i++) {
        enter = 0;
        pthread_create(&td, NULL, thread_fn, NULL); 
        pthread_mutex_lock(&mutex);
        while (!enter) {
            pthread_mutex_unlock(&mutex);
            pthread_mutex_lock(&mutex);
        }
        pthread_cond_signal(&cond_wait);
        START_COUNT(high, low);
        pthread_mutex_unlock(&mutex);
        pthread_join(td, NULL);
        start = ((unsigned long long) high << 32) | low;
        end = ((unsigned long long) hight << 32) | lowt;
        printf("%llu\n", end - start);
    }

    return 0;
}
