cmake_minimum_required(VERSION 3.23)
project(Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    
    SRC_DIR "${PROJECT_SOURCE_DIR}/src"
)

include_directories(include)


add_executable(exec

    ${SRC_DIR}/Parser.cpp
    ${SRC_DIR}/main.cpp
)


if(UNIX)

    target_compile_options(exec PRIVATE -Wall -Wextra -Wpedantic)

elseif(WIN32)

    target_compile_options(exec PRIVATE /W4)

endif()