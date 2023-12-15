cmake_minimum_required(VERSION 3.19)
project(AdventOfCode2023)
set(CMAKE_CXX_STANDARD 11)

subdirs(Day01)
subdirs(Day02)
subdirs(Day03)
subdirs(Day04)
subdirs(Day05)
subdirs(Day06)
subdirs(Day07)
subdirs(Day08)
subdirs(Day09)
subdirs(Day10)
subdirs(Day11)
subdirs(Day12)
subdirs(Day13)
subdirs(Day14)

add_executable(aoc_driver main.cpp)

target_include_directories(aoc_driver PUBLIC ${CMAKE_SOURCE_DIR}/Common)

target_link_libraries(aoc_driver PUBLIC day01
                                        day02
                                        day03
                                        day04
                                        day05
                                        day06
                                        day07
                                        day08
                                        day09
                                        day10
                                        day11
                                        day12
                                        day13
                                        day14)