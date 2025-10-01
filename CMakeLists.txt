cmake_minimum_required(VERSION 4.0)
project(afl_4_ancestry C)

set(CMAKE_C_STANDARD 23)

add_executable(afl_4_ancestry
        main.c
        ancestry.c
        ancestry.h
)
