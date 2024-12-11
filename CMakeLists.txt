cmake_minimum_required(VERSION 3.29)
project(PD2test C)

set(CMAKE_C_STANDARD 23)

add_executable(PD2test main.c
        Vector.h
        Vector.c
        Node.h
        Node.c
)
