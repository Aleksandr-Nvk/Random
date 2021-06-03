#include <stdio.h>
#include "library.h"

int main(void) {
    Random stream = new_random(501235891);

    clock_t start = clock();

    for (int i = 0; i < 100000000; ++i) {
        uint32_t val = random_int();
        if (val > 100000) {
            continue;
        }
        printf("%u\n", val);
    }

    printf("\nDone in %lf sec", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

    return 0;
}