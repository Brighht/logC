cmake_minimum_required(VERSION 3.30)
project(cLog C)

set(CMAKE_C_STANDARD 23)

add_library(cLog SHARED library.c)
