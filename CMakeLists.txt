cmake_minimum_required(VERSION 3.8)
project(avl_map)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
