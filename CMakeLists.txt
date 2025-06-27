cmake_minimum_required(VERSION 3.10)

# C++11機能を有効にする
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(1DHeatConduction CXX)

add_executable(heat_conduction 
    src/makeMatrixEquation.cpp
    src/meshGeneration.cpp
    src/main.cpp
    src/solver.cpp
    include/makeMatrixEquation.h
    include/meshGeneration.h
    include/main.h
    include/solver.h
)

target_include_directories(heat_conduction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

