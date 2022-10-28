cmake_minimum_required(VERSION 3.23)
project(Tarea2Datos2)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

enable_testing()

add_subdirectory(test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(Tarea2Datos2 main.cpp)
target_link_libraries(Tarea2Datos2
        gtest
        gtest_main
        gmock_main)


