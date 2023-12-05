cmake_minimum_required(VERSION 3.19)
project(AdventOfCode2023)
set(CMAKE_CXX_STANDARD 11)

subdirs(Day01)
subdirs(Day02)
subdirs(Day03)
subdirs(Day04)
subdirs(Day05)

add_executable(aoc_driver main.cpp)

target_include_directories(aoc_driver PUBLIC ${CMAKE_SOURCE_DIR}/Common)

target_link_libraries(aoc_driver PUBLIC day01 day02 day03 day04 day05)