#include "random.h"

                                        /* *** UNSIGNED 64-BIT INTEGER *** */

/* returns a new uint64_t stream seeded with 'seed' */
Random64 new_rand64(uint64_t seed) {
    Random64 new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = new_stream.current = seed;
    return new_stream;
}

/* xorshift algorithm for uint64_t values */
uint64_t xorshift64(uint64_t current) {
    current ^= current << 12;        /* see more triplets in the end of this file */
    current ^= current >> 25;
    current ^= current << 27;

    return current;
}

/* returns the next uint64_t value from 'stream' */
uint64_t next64(Random64* stream) {
    return stream->current = xorshift64(stream->current);
}

uint64_t rand64_non_stream = 0;    /* current non-stream uint64_t value */

/* returns a random uint64_t value */
uint64_t rand64(void) {
    if (rand64_non_stream == 0) {
        rand64_non_stream = time(NULL);
    }

    return rand64_non_stream = xorshift64(rand64_non_stream);
}

                                        /* *** UNSIGNED 32-BIT INTEGER *** */

/* returns a new uint32_t stream seeded with 'seed' */
Random32 new_rand32(uint32_t seed) {
    Random32 new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = new_stream.current = seed;
    return new_stream;
}

/* xorshift algorithm for uint32_t values */
uint32_t xorshift32(uint32_t current) {
    current ^= current << 13;        /* see more triplets in the end of this file */
    current ^= current >> 17;
    current ^= current << 5;

    return current;
}

/* returns the next uint32_t value from 'stream' */
uint32_t next32(Random32* stream) {
    return stream->current = xorshift32(stream->current);
}

uint32_t rand32_non_stream = 0;    /* current non-stream uint32_t value */

/* returns a random uint32_t value */
uint32_t rand32(void) {
    if (rand32_non_stream == 0) {
        rand32_non_stream = time(NULL);
    }

    return rand32_non_stream = xorshift32(rand32_non_stream);
}

                                        /* *** UNSIGNED 16-BIT INTEGER *** */

/* returns a new uint16_t stream seeded with 'seed' */
Random16 new_rand16(uint16_t seed) {
    Random16 new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = new_stream.current = seed;
    return new_stream;
}

/* xorshift algorithm for uint16_t values */
uint16_t xorshift16(uint16_t current) {
    current ^= current << 6;        /* see more triplets in the end of this file */
    current ^= current >> 3;
    current ^= current << 8;

    return current;
}

/* returns the next uint16_t value from 'stream' */
uint16_t next16(Random16* stream) {
    return stream->current = xorshift16(stream->current);
}

uint16_t rand16_non_stream = 0;    /* current non-stream uint16_t value */

/* returns a random uint16_t value */
uint16_t rand16(void) {
    if (rand16_non_stream == 0) {
        rand16_non_stream = time(NULL);
    }

    return rand16_non_stream = xorshift16(rand16_non_stream);
}

                                        /* *** UNSIGNED 8-BIT INTEGER *** */

/* returns a new uint8_t stream seeded with 'seed' */
Random8 new_rand8(uint8_t seed) {
    Random8 new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = new_stream.current = seed;
    return new_stream;
}

/* xorshift algorithm for uint8_t values */
uint8_t xorshift8(uint8_t current) {
    current ^= current << 7;        /* see more triplets in the end of this file */
    current ^= current >> 5;
    current ^= current << 3;

    return current;
}

/* returns the next uint8_t value from 'stream' */
uint8_t next8(Random8* stream) {
    return stream->current = xorshift8(stream->current);
}

uint8_t rand8_non_stream = 0;    /* current non-stream uint8_t value */

/* returns a random uint8_t value */
uint8_t rand8(void) {
    if (rand8_non_stream == 0) {
        rand8_non_stream = time(NULL);
    }

    return rand8_non_stream = xorshift8(rand8_non_stream);
}

                                        /* *** BOOL (0 or 1) *** */

/* returns a new bool stream seeded with 'seed' */
RandomBool new_rand_bool(uint8_t seed) {
    RandomBool new_stream;

    if (seed == 0) {
        perror("SEED MUST BE A NON-ZERO VALUE");
    }

    new_stream.seed = new_stream.current = seed;
    return new_stream;
}

/* returns the next bool value (0 or 1) from 'stream' */
uint8_t next_bool(RandomBool* stream) {
    stream->current = xorshift8(stream->current);
    return stream->current & 1;
}

uint8_t rand_bool_non_stream = 0;    /* current non-stream bool value */

/* returns either 0 or 1 randomly */
uint8_t rand_bool(void) {
    if (rand_bool_non_stream == 0) {
        rand_bool_non_stream = time(NULL);
    }

    rand_bool_non_stream = xorshift8(rand_bool_non_stream);
    return rand_bool_non_stream & 1;
}
                                        /* *** ADDITIONAL HANDY FUNCTIONS *** */

/* returns a random int64_t value between min inclusive and max inclusive */
int64_t rand_int_range(int64_t min, int64_t max) {
    /* simple validity checks */
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    }

    if (min == max) {
        return min;
    }

    return (rand32() % (max - min + 1) + min);
}

/* returns a random long double value between min inclusively and max inclusively */
long double rand_l_double_range(long double min, long double max) {
    /* simple validity checks */
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    }

    if (min == max) {
        return min;
    }

    long double rand = (long double)rand64() / (long double)UINT64_MAX;
    long double fraction = rand * (max - min);

    return min + fraction;
}

/* returns a random double value between min inclusively and max inclusively */
double rand_double_range(double min, double max) {
    /* simple validity checks */
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    }

    if (min == max) {
        return min;
    }

    double rand = (double)rand64() / (double)UINT64_MAX;
    double fraction = rand * (max - min);

    return min + fraction;
}

/* returns a random float value between min inclusively and max inclusively */
float rand_float_range(float min, float max) {
    /* simple validity checks */
    if (min > max) {
        perror("min MUST BE LESS THAN max");
        return 0;
    }

    if (min == max) {
        return min;
    }

    float rand = (float)rand64() / (float)UINT64_MAX;
    float fraction = rand * (max - min);

    return min + fraction;
}


/*
TRIPLETS FOR 64-BIT INTEGERS:

| 1, 1,54| 1, 1,55| 1, 3,45| 1, 7, 9| 1, 7,44| 1, 7,46| 1, 9,50| 1,11,35| 1,11,50|
| 1,13,45| 1,15, 4| 1,15,63| 1,19, 6| 1,19,16| 1,23,14| 1,23,29| 1,29,34| 1,35, 5|
| 1,35,11| 1,35,34| 1,45,37| 1,51,13| 1,53, 3| 1,59,14| 2,13,23| 2,31,51| 2,31,53|
| 2,43,27| 2,47,49| 3, 1,11| 3, 5,21| 3,13,59| 3,21,31| 3,25,20| 3,25,31| 3,25,56|
| 3,29,40| 3,29,47| 3,29,49| 3,35,14| 3,37,17| 3,43, 4| 3,43, 6| 3,43,11| 3,51,16|
| 3,53, 7| 3,61,17| 3,61,26| 4, 7,19| 4, 9,13| 4,15,51| 4,15,53| 4,29,45| 4,29,49|
| 4,31,33| 4,35,15| 4,35,21| 4,37,11| 4,37,21| 4,41,19| 4,41,45| 4,43,21| 4,43,31|
| 4,53, 7| 5, 9,23| 5,11,54| 5,15,27| 5,17,11| 5,23,36| 5,33,29| 5,41,20| 5,45,16|
| 5,47,23| 5,53,20| 5,59,33| 5,59,35| 5,59,63| 6, 1,17| 6, 3,49| 6,17,47| 6,23,27|
| 6,27, 7| 6,43,21| 6,49,29| 6,55,17| 7, 5,41| 7, 5,47| 7, 5,55| 7, 7,20| 7, 9,38|
| 7,11,10| 7,11,35| 7,13,58| 7,19,17| 7,19,54| 7,23, 8| 7,25,58| 7,27,59| 7,33, 8|
| 7,41,40| 7,43,28| 7,51,24| 7,57,12| 8, 5,59| 8, 9,25| 8,13,25| 8,13,61| 8,15,21|
| 8,25,59| 8,29,19| 8,31,17| 8,37,21| 8,51,21| 9, 1,27| 9, 5,36| 9, 5,43| 9, 7,18|
| 9,19,18| 9,21,11| 9,21,20| 9,21,40| 9,23,57| 9,27,10| 9,29,12| 9,29,37| 9,37,31|
| 9,41,45|10, 7,33|10,27,59|10,53,13|11, 5,32|11, 5,34|11, 5,43|11, 5,45|11, 9,14|
|11, 9,34|11,13,40|11,15,37|11,23,42|11,23,56|11,25,48|11,27,26|11,29,14|11,31,18|
|11,53,23|12, 1,31|12, 3,13|12, 3,49|12, 7,13|12,11,47|12,25,27|12,39,49|12,43,19|
|13, 3,40|13, 3,53|13, 7,17|13, 9,15|13, 9,50|13,13,19|13,17,43|13,19,28|13,19,47|
|13,21,18|13,21,49|13,29,35|13,35,30|13,35,38|13,47,23|13,51,21|14,13,17|14,15,19|
|14,23,33|14,31,45|14,47,15|15, 1,19|15, 5,37|15,13,28|15,13,52|15,17,27|15,19,63|
|15,21,46|15,23,23|15,45,17|15,47,16|15,49,26|16, 5,17|16, 7,39|16,11,19|16,11,27|
|16,13,55|16,21,35|16,25,43|16,27,53|16,47,17|17,15,58|17,23,29|17,23,51|17,23,52|
|17,27,22|17,45,22|17,47,28|17,47,29|17,47,54|18, 1,25|18, 3,43|18,19,19|18,25,21|
|18,41,23|19, 7,36|19, 7,55|19,13,37|19,15,46|19,21,52|19,25,20|19,41,21|19,43,27|
|20, 1,31|20, 5,29|21, 1,27|21, 9,29|21,13,52|21,15,28|21,15,29|21,17,24|21,17,30|
|21,17,48|21,21,32|21,21,34|21,21,37|21,21,38|21,21,40|21,21,41|21,21,43|21,41,23|
|22, 3,39|23, 9,38|23, 9,48|23, 9,57|23,13,38|23,13,58|23,13,61|23,17,25|23,17,54|
|23,17,56|23,17,62|23,41,34|23,41,51|24, 9,35|24,11,29|24,25,25|24,31,35|25, 7,46|
|25, 7,49|25, 9,39|25,11,57|25,13,29|25,13,39|25,13,62|25,15,47|25,21,44|25,27,27|
|25,27,53|25,33,36|25,39,54|28, 9,55|28,11,53|29,27,37|31, 1,51|31,25,37|31,27,35|
|33,31,43|33,31,55|43,21,46|49,15,61|55, 9,56|
*/

/*
TRIPLETS FOR 32-BIT INTEGERS:

| 1, 3,10| 1, 5,16| 1, 5,19| 1, 9,29| 1,11, 6| 1,11,16| 1,19, 3| 1,21,20| 1,27,27|
| 2, 5,15| 2, 5,21| 2, 7, 7| 2, 7, 9| 2, 7,25| 2, 9,15| 2,15,17| 2,15,25| 2,21, 9|
| 3, 1,14| 3, 3,26| 3, 3,28| 3, 3,29| 3, 5,20| 3, 5,22| 3, 5,25| 3, 7,29| 3,13, 7|
| 3,23,25| 3,25,24| 3,27,11| 4, 3,17| 4, 3,27| 4, 5,15| 5, 3,21| 5, 7,22| 5, 9,7 |
| 5, 9,28| 5, 9,31| 5,13, 6| 5,15,17| 5,17,13| 5,21,12| 5,27, 8| 5,27,21| 5,27,25|
| 5,27,28| 6, 1,11| 6, 3,17| 6,17, 9| 6,21, 7| 6,21,13| 7, 1, 9| 7, 1,18| 7, 1,25|
| 7,13,25| 7,17,21| 7,25,12| 7,25,20| 8, 7,23| 8,9,23 | 9, 5,1 | 9, 5,25| 9,11,19|
| 9,21,16|10, 9,21|10, 9,25|11, 7,12|11, 7,16|11,17,13|11,21,13|12, 9,23|13, 3,17|
|13, 3,27|13, 5,19|13,17,15|14, 1,15|14,13,15|15, 1,29|17,15,20|17,15,23|17,15,26|
*/

/*
TRIPLETS FOR 16-BIT INTEGERS:

| 1, 1, 7| 1, 1,12| 1, 1,13| 2, 5, 8| 2, 5,13| 2,13,15| 2,15,13| 3, 7, 6| 5, 3, 1|
| 5, 3, 8| 5, 3,13|	5, 7, 4| 6, 3, 8| 7, 1, 6| 7, 1,15| 7, 2, 1| 8, 3, 9| 9,14, 5|
|11, 8, 5|13,12, 3|14, 1,15|15,10, 1|
*/

/*
TRIPLETS FOR 8-BIT INTEGERS:

| 1, 1, 3| 3, 3, 2| 5, 3, 2| 7, 5, 3|
*/