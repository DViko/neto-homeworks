cmake_minimum_required(VERSION 3.20)
project(data_base_05)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)

add_executable(exec
    src/main.cpp
)

target_link_libraries(exec PRIVATE
    dbase
    config
)
