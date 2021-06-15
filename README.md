# Random
This is a fast, efficient and extended version of built-in API for generating random values.
Random API comprises functions for generating 8-, 16-, 32-, 64-bit integers, bool and floating-point values using the [Xorshift](https://en.wikipedia.org/wiki/Xorshift) algorithm. Values can also be generated in specified range.
Random API also supports seeds. You can create an OOP-like stream of values of particular type, based on initial seed. Default triplets used for Xorshift have huge period, hence, no patterns of generated sequences can be tracked.
Example of usage can be seen in [usage.c](https://github.com/Aleksandr-Nvk/Random/blob/main/usage.c). Source code is situated in [random.c](https://github.com/Aleksandr-Nvk/Random/blob/main/source/random.c).
