cmake_minimum_required(VERSION 3.31)
project(day_nine_part_one)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(day_nine_part_one)
target_sources(day_nine_part_one PRIVATE
  src/main.cpp
)
