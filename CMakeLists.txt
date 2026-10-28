cmake_minimum_required(VERSION 3.14)
project(lab2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ip_filter_lib code/ip_filter.cpp)
target_include_directories(ip_filter_lib PUBLIC include)

add_executable(ip_filter code/main.cpp)
target_link_libraries(ip_filter PRIVATE ip_filter_lib)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.14.0)
    FetchContent_MakeAvailable(googletest)

    add_executable(ip_filter_tests tests/test_ip_filter.cpp)
    target_link_libraries(ip_filter_tests PRIVATE ip_filter_lib GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(ip_filter_tests)
endif()