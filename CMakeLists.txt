cmake_minimum_required(VERSION 3.19)
project(Random C)

set(CMAKE_C_STANDARD 99)

add_executable(Main usage.c include/random.h)

include_directories(include)

find_library(Random random lib)
target_link_libraries(Main LINK_PUBLIC ${Random})