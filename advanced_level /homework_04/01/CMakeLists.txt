cmake_minimum_required(VERSION 3.23)
project(unit_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/tests")
set(CATCH_DIR "${PROJECT_SOURCE_DIR}/external")


set(SOURCES

    ${CATCH_DIR}/catch_amalgamated.cpp
    ${TEST_DIR}/test_list.cpp
)


add_executable(test_exec ${SOURCES})

target_include_directories(test_exec PRIVATE

    ${SRC_DIR}
    ${CATCH_DIR}
)


if(UNIX)

    target_compile_options(test_exec PRIVATE -Wall -Wextra -Wpedantic)

elseif(WIN32)

    target_compile_options(test_exec PRIVATE /W4)

endif()