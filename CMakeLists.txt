cmake_minimum_required(VERSION 3.15)

project(AoC2025)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)


add_library(Matrix SHARED ${CMAKE_CURRENT_SOURCE_DIR}/includes/Matrix.h ${CMAKE_CURRENT_SOURCE_DIR}/includes/Matrix.cpp)
target_include_directories(Matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_library(UnionFind SHARED ${CMAKE_CURRENT_SOURCE_DIR}/includes/UnionFind.h ${CMAKE_CURRENT_SOURCE_DIR}/includes/UnionFind.cpp)
target_include_directories(UnionFind PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_executable(d1p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day1/d1_p1.cpp)
add_executable(d1p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day1/d1_p2.cpp)

add_executable(d2p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day2/d2_p1.cpp)
add_executable(d2p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day2/d2_p2.cpp)

add_executable(d3p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day3/d3_p1.cpp)
add_executable(d3p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day3/d3_p2.cpp)

add_executable(d4p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day4/d4_p1.cpp)
target_link_libraries(d4p1 PRIVATE Matrix)
add_executable(d4p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day4/d4_p2.cpp)
target_link_libraries(d4p2 PRIVATE Matrix)

add_executable(d5p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day5/d5_p1.cpp)
add_executable(d5p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day5/d5_p2.cpp)

add_executable(d6p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day6/d6_p1.cpp)
add_executable(d6p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day6/d6_p2.cpp)

add_executable(d7p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day7/d7_p1.cpp)
target_link_libraries(d7p1 PRIVATE Matrix)
add_executable(d7p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day7/d7_p2.cpp)
target_link_libraries(d7p2 PRIVATE Matrix)

add_executable(d8p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day8/d8_p1.cpp)
target_link_libraries(d8p1 PRIVATE UnionFind)
add_executable(d8p2 ${CMAKE_CURRENT_SOURCE_DIR}/Day8/d8_p2.cpp)
target_link_libraries(d8p2 PRIVATE UnionFind)

add_executable(d9p1 ${CMAKE_CURRENT_SOURCE_DIR}/Day9/d9_p1.cpp)





