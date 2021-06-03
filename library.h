#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RAND_INT    (UINT32_MAX - 4)   /* max possible random uint32_t value (6 last values lost) */
#define A_MULTIPLIER    3870709308         /* pre-calculated multiplier 'a', defined in tables */

/* linear congruential generator for suitable amount of values */
#define LCG_RAND(current)   ((A_MULTIPLIER * (current)) % MAX_RAND_INT);

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
Random new_rand(uint32_t seed) {
    Random new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = seed;
    new_stream.current = LCG_RAND(seed)
    return new_stream;
}

/* returns the next random uint32_t integer from a stream */
uint32_t next(Random* stream) {
    return stream->current = LCG_RAND(stream->current)
}

/* returns a random uint32_t integer */
uint32_t rand_int(void) {
    if (current == 0) {
        current = (uint32_t)time(NULL);
    }

    return current = LCG_RAND(current)
}

/* returns a random int32_t integer between min inclusively and max inclusively */
int32_t random_int_range(int32_t min, int32_t max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    return (int32_t) rand_int() % ((max - min + 1)) + min;
}

/* returns a random long double value between min inclusively and max inclusively */
long double rand_l_double_range(long double min, long double max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    long double rand = ((long double) rand_int()) / (long double)(MAX_RAND_INT);
    long double fraction = rand * (max - min);

    return min + fraction;
}

/* returns a random double value between min inclusively and max inclusively */
double rand_double_range(double min, double max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    double rand = ((double) rand_int()) / (double)(MAX_RAND_INT);
    double fraction = rand * (max - min);

    return min + fraction;
}

/* returns a random float value between min inclusively and max inclusively */
float rand_float_range(float min, float max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    float rand = ((float) rand_int()) / (float)(MAX_RAND_INT - 1);
    float fraction = rand * (max - min);

    return min + fraction;
}