cmake_minimum_required(VERSION 3.31)
project(day_one_part_two)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day_one_part_two)
target_sources(day_one_part_two PRIVATE
  src/main.cpp
)
