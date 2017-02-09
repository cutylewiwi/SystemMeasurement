#ifndef TIMING_H
#define TIMING_H

#define START_COUNT(cycles_high, cycles_low)      \
    asm volatile ("CPUID\n\t" "RDTSC\n\t" \
                  "mov %%edx, %0\n\t" \
                  "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::\
                  "%rax", "%rbx", "%rcx", "%rdx")

#define STOP_COUNT(cycles_high1, cycles_low1)     \
    asm volatile ("RDTSCP\n\t" \
                  "mov %%edx, %0\n\t" "mov %%eax, %1\n\t" \
                  "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: \
                  "%rax", "%rbx", "%rcx", "%rdx")

//warm up to fill instruction cache
#define WARMUP(high, low, high1, low1)\
do {\
    START_COUNT(high, low); \
    STOP_COUNT(high1, low1);\
    START_COUNT(high, low); \
    STOP_COUNT(high1, low1);\
    START_COUNT(high, low); \
    STOP_COUNT(high1, low1);\
} while(0)
#endif
