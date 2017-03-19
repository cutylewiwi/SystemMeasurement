#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHUNKS      (1ll << 22)
#define PAGE        (1ll << 12)       // page size
#define STRIDE      64

#define FILEPATH    "pagefaultmmap.tmp"
#define FILESIZE    (CHUNKS * PAGE)

int main (){
    unsigned long long i;

    srand((unsigned) time(NULL));

    for (i = 0; i < FILESIZE; i++) {
        printf("%c", rand() % 128);
    }

    return 0;
}
