cmake_minimum_required(VERSION 3.20)
project(Custom_std_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(APP_DIR ${CMAKE_BINARY_DIR}/bin)

add_library(compiler_warnings INTERFACE)


if(MSVC)

    target_compile_options(compiler_warnings INTERFACE
        /W4
        /O2
    )

else()

    target_compile_options(compiler_warnings INTERFACE

        -Wall -Wextra -Wpedantic -Wshadow -Werror
    )

endif()


add_library(custom_vector SHARED

    src/IntVector.cpp
)

target_include_directories(custom_vector PUBLIC

    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(custom_vector PROPERTIES

    LIBRARY_OUTPUT_DIRECTORY  ${APP_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${APP_DIR}/lib

    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_link_libraries(custom_vector PRIVATE compiler_warnings)


add_executable(exec main.cpp)

set_target_properties(exec PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY ${APP_DIR}
)

target_link_libraries(exec PRIVATE

    custom_vector
    compiler_warnings
)