cmake_minimum_required(VERSION 3.10)
project(Homework_04_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(exec
    main.cpp
    src/AddressFormat.cpp
)

add_custom_command(

    TARGET exec POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/files
        ${CMAKE_BINARY_DIR}/files
)

target_include_directories(exec PRIVATE include)

if(MSVC)

    target_compile_options(exec PRIVATE /W4 /O2)

else()

    target_compile_options(exec PRIVATE
        -Wall -Wextra -O2 -Wpedantic -Wshadow
        -Wconversion -Wsign-conversion -Wold-style-cast -Wcast-align
        -Wduplicated-cond -Wlogical-op -Werror
    )

endif()