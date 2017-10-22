project(test)

add_subdirectory(lib/googletest-release-1.8.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests AvlMapTest.cpp ../include/avl_map.h ../include/avl_tree.h)
target_link_libraries(runTests avl_tree gtest gtest_main)
