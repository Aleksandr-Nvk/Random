#include "random.h"

int main(void) {
    /* test */
    for (int i = 0; i < 100; ++i) {
        printf("%lld\n", rand_int_range(0, 10));
    }

    return 0;
}