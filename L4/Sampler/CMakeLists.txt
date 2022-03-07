cmake_minimum_required(VERSION 3.1)
project(sampler VERSION 0.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra")

add_subdirectory(libsampler)
add_subdirectory(programs)
add_subdirectory(tools)
