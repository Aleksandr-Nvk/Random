#include <stdio.h>
#include <time.h>
#include "random.h"

int main(void) {
    Random stream = new_rand(501235891);

    clock_t start = clock();

    for (int i = 0; i < 10000; ++i) {
        printf("\n%d", rand_bool().uint32);
    }

    printf("\nDone in %lf secs", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

    return 0;
}