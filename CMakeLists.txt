cmake_minimum_required(VERSION 3.17)
project(neuro_kohonen C)

set(CMAKE_C_STANDARD 99)

add_executable(neuro_kohonen main.c header.h reader.c)
target_link_libraries(neuro_kohonen m)