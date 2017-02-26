#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHUNKS      3000
#define PAGE        (1 << 12)       // page size
#define STRIDE      60

#define FILEPATH    "/tmp/pagefaultmmap.tmp"
#define FILESIZE    (CHUNKS * PAGE)

int main (){
    int i;

    srand((unsigned) time(NULL));

    for (i = 0; i < FILESIZE; i++) {
        printf("%c", rand() % 128);
    }

    return 0;
}
