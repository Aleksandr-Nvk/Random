#include <stdio.h>
#include "library.h"

int main(void) {
    Random stream = new_rand(501235891);

    clock_t start = clock();

    for (int i = 0; i < 100; ++i) {
        printf("%.30f\n", rand_float_range(-100000.5f, 100000.5f));
    }

    printf("\nDone in %lf secs", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

    return 0;
}