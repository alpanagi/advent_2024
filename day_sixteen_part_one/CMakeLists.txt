cmake_minimum_required(VERSION 3.11)
project(day_sixteen_part_one)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(day_sixteen_part_one)
target_sources(day_sixteen_part_one PRIVATE
    src/code.cpp
)

add_executable(app)
target_link_libraries(app day_sixteen_part_one)
target_sources(app PRIVATE
    src/main.cpp
)

add_executable(test)
target_link_libraries(test day_sixteen_part_one)
target_sources(test PRIVATE
    src/test.cpp
)
