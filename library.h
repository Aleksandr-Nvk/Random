#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A_MULTIPLIER 3870709308     /* pre-calculated multiplier 'a', defined in tables */

/* linear congruential generator for suitable amount of values (6 values lost) */
#define LCG_RAND(current) ((A_MULTIPLIER * (current)) % (UINT32_MAX - 4));

uint32_t current;    /* current auto-generated seed */

/* basic random stream structure. Should not be changed manually */
typedef struct Random {
    uint32_t seed;
    uint32_t current;
} Random;

/* set a new non-zero seed to a stream */
void set_seed(Random* stream, uint32_t seed) {
    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    } else {
        stream->seed = seed;
    }
}

/* returns a new stream of random integers generated from a seed */
Random new_random(uint32_t seed) {
    Random new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = seed;
    new_stream.current = LCG_RAND(seed);
    return new_stream;
}


/* returns the next random uint32_t integer from a stream */
uint32_t next(Random* stream) {
    return stream->current = LCG_RAND(stream->current);
}

/* returns a random uint32_t integer */
uint32_t random_int(void) {
    if (current == 0) {
        current = (uint32_t)time(NULL);
    }

    return current = LCG_RAND(current);
}

/* returns a random uint32_t integer between min inclusively and max inclusively */
int32_t random_int_range(int32_t min, int32_t max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    return (int32_t)random_int() % ((max - min + 1)) + min;
}