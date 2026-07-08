cmake_minimum_required(VERSION 3.20)

project(design_patterns_01_03 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    INC_DIR "${PROJECT_SOURCE_DIR}/include"
)

set(
    SRC_DIR "${PROJECT_SOURCE_DIR}/src"
)


include_directories(${INC_DIR})

add_executable(exec

    ${SRC_DIR}/main.cpp
)