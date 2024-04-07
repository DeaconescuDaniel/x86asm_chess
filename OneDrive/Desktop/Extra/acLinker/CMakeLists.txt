cmake_minimum_required(VERSION 3.26)
project(acLinker C)

set(CMAKE_C_STANDARD 11)

add_executable(acLinker main.c
        tokens.h
        tokens.c)
