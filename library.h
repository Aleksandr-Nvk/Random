#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RAND_INT    (INT64_MAX - 1)                   /* max possible random integer value (last value lost) */
#define A_MULTIPLIER    4645906587823291368         /* pre-calculated multiplier 'a', defined in tables */

/* linear congruential generator for suitable amount of integers */
#define LCG_RAND(current)   ((A_MULTIPLIER * (current)) % (MAX_RAND_INT + 1))

typedef union random {
    uint64_t uint64;
    uint32_t uint32;
    uint16_t uint16;
    uint8_t  uint8;

    int64_t int64;
    int32_t int32;
    int16_t int16;
    int8_t  int8;
} value;

/* basic random stream structure. Should not be changed manually */
typedef struct Random {
    uint64_t seed;
    value current;
} Random;

value current;    /* current auto-generated value */

/* set a new non-zero seed to a stream */
void set_seed(Random* stream, uint64_t seed) {
    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    } else {
        stream->seed = seed;
    }
}

/* returns a new stream of random integers generated from a seed */
Random new_rand(uint64_t seed) {
    Random new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = seed;
    new_stream.current.uint64 = LCG_RAND(seed);
    return new_stream;
}

/* returns the next random integer from a stream */
value next(Random* stream) {
    stream->current.uint64 = LCG_RAND(stream->current.uint64);
    return stream->current;
}

/* returns a random integer */
value rand_uint(void) {
    if (current.uint64 == 0) {
        current.uint64 = (uint64_t)time(NULL);
    }

    current.uint64 = LCG_RAND(current.uint64);
    return current;
}

/* returns a random integer between min inclusively and max inclusively */
value rand_int_range(int64_t min, int64_t max) {
    value result;

    if (min > max) {
        perror("min MUST BE LESS THAN max");
        result.uint64 = 0;
    } else if (min == max) {
        result.uint64 = min;
    } else {
        result.uint64 = (rand_uint().uint64 % (max - min + 1) + min);
    }

    return result;
}

/* returns a random long double value between min inclusively and max inclusively */
long double rand_l_double_range(long double min, long double max) {
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    } else if (min == max) {
        return min;
    }

    long double rand = (long double)rand_uint().uint64 / (long double)MAX_RAND_INT;
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

    double rand = (double)rand_uint().uint64 / (double)MAX_RAND_INT;
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

    float rand = (float)rand_uint().uint64 / (float)MAX_RAND_INT;
    float fraction = rand * (max - min);

    return min + fraction;
}

/* returns either 0 or 1 randomly */
value rand_bool() {
    return rand_int_range(0, 1);
}