cmake_minimum_required(VERSION 3.10)
project(Homework_08_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES

    main.cpp  
)

add_executable(exec ${SOURCES})

if(MSVC)

    target_compile_options(exec PRIVATE /W4 /O2)

else()

    target_compile_options(exec PRIVATE
        -Wall -Wextra -O2 -Wpedantic -Wshadow
        -Wconversion -Wsign-conversion -Wold-style-cast -Wcast-align
        -Wduplicated-cond -Wlogical-op -Werror
    )

endif()