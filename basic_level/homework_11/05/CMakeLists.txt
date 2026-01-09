cmake_minimum_required(VERSION 3.20)
project(Homework_11_05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(APP_DIR ${CMAKE_BINARY_DIR}/app)

add_library(compiler_warnings INTERFACE)


if(MSVC)

    target_compile_options(compiler_warnings INTERFACE
        /W4
        /O2
    )

else()

    target_compile_options(compiler_warnings INTERFACE

        -Wall -Wextra -Wpedantic -Wshadow
        -Wconversion -Wsign-conversion
        -Wold-style-cast -Wcast-align
        -Wduplicated-cond -Wlogical-op
        -Werror
        -O2
    )

endif()


add_library(shapes SHARED

    src/Quadrilaterals.cpp
    src/Triangulars.cpp
    src/Factory.cpp
    src/Logger.cpp
)

target_include_directories(shapes PUBLIC

    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(shapes PROPERTIES

    LIBRARY_OUTPUT_DIRECTORY  ${APP_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${APP_DIR}/lib

    POSITION_INDEPENDENT_CODE ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_link_libraries(shapes PRIVATE compiler_warnings)


add_executable(exec main.cpp)

set_target_properties(exec PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY ${APP_DIR}
)

target_link_libraries(exec PRIVATE

    shapes
    compiler_warnings
)