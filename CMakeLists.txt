cmake_minimum_required(VERSION 3.30)
project(Log C)


set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)


add_library(cLog SHARED library.c)


# Optional: Enable compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(library.c PRIVATE -Wall -Wextra -pedantic)
endif()
