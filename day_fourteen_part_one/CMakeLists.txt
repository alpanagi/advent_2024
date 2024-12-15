cmake_minimum_required(VERSION 3.10)
project(day_fourteen_part_one)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(day_fourteen_part_one)
target_sources(day_fourteen_part_one PRIVATE
    src/main.cpp
)

