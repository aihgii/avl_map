project(benchmark)

add_subdirectory(lib/benchmark-1.2.0)
include_directories(lib/benchmark-1.2.0/include)

add_executable(runBenchmark AvlMapBenchmark.cpp ../include/avl_map.h ../include/avl_tree.h)
target_link_libraries(runBenchmark avl_tree benchmark)
