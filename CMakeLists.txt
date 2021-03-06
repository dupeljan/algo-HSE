cmake_minimum_required(VERSION 2.8)

project(Lab)

add_executable(${PROJECT_NAME}
    main.cpp
    quick_sort.h
    two_three_tree.h
    two_three_tree.cpp
    sweep_line.h
    sweep_line.cpp
    segment.h
)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

## Add Gtest
enable_testing()
add_executable(runUnitTests
    unittests.cpp
    quick_sort.h
    two_three_tree.h
    two_three_tree.cpp
    sweep_line.h
    sweep_line.cpp
    segment.h
)

target_link_libraries(runUnitTests gtest gtest_main Threads::Threads)

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
