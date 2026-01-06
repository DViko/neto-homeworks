cmake_minimum_required(VERSION 3.20)
project(Homework_11_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_DIR
    
    ${CMAKE_BINARY_DIR}/app
)

add_library(greeter STATIC src/Greeter.cpp)

target_include_directories(greeter PRIVATE

    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(greeter PROPERTIES

    ARCHIVE_OUTPUT_DIRECTORY ${APP_DIR}/lib
)


add_executable(exec main.cpp)

target_include_directories(exec PRIVATE

    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(exec PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY ${APP_DIR}
)

target_link_libraries(exec PRIVATE greeter)


if(MSVC)

    target_compile_options(exec PRIVATE /W4 /O2)

else()

    target_compile_options(exec PRIVATE
    
        -Wall -Wextra -O2 -Wpedantic -Wshadow
        -Wconversion -Wsign-conversion -Wold-style-cast -Wcast-align
        -Wduplicated-cond -Wlogical-op -Werror
    )

endif()