cmake_minimum_required(VERSION 3.17)
project(activity_calc C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -pedantic -Wall -Werror")

include_directories(.)

add_executable(hash.h
        hash.c
        hash_tests.c)
