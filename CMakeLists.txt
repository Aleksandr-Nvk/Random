cmake_minimum_required(VERSION 3.19)
project(Random C)

set(CMAKE_C_STANDARD 99)

add_executable(Main usage.c random.h random_source/random.c)

include_directories(include)
