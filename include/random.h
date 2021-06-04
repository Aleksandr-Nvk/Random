#include <stdlib.h>

#define MAX_RAND_INT    (INT64_MAX - 1)                   /* max possible random integer value (last value lost) */
#define A_MULTIPLIER    4645906587823291368         /* pre-calculated multiplier 'a', defined in tables */

typedef union random {
    long long llong_int;
    long      long_int;
    int       int_int;
    short     short_int;
    char      char_int;

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
void set_seed(Random* stream, uint64_t seed);

/* returns a new stream of random integers generated from a seed */
Random new_rand(uint64_t seed);

/* returns the next random integer from a stream */
value next(Random* stream);

/* returns a random integer */
value rand_uint(void);

/* returns a random integer between min inclusively and max inclusively */
value rand_int_range(int64_t min, int64_t max);

/* returns a random long double value between min inclusively and max inclusively */
long double rand_l_double_range(long double min, long double max);

/* returns a random double value between min inclusively and max inclusively */
double rand_double_range(double min, double max);

/* returns a random float value between min inclusively and max inclusively */
float rand_float_range(float min, float max);

/* returns either 0 or 1 randomly */
value rand_bool(void);