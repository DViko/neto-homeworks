cmake_minimum_required(VERSION 3.20)

project(data_base_05)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(PROJECT_WARNINGS
    -Wall
    -Wextra
    -Wpedantic
)

add_subdirectory(external)
add_subdirectory(domain)
add_subdirectory(cli)

add_executable(exec
    src/main.cpp
    src/application.cpp
)

target_include_directories(exec PRIVATE
    ${CMAKE_SOURCE_DIR}/domain/include
    ${CMAKE_SOURCE_DIR}/external/dbase/include
    ${CMAKE_SOURCE_DIR}/cli/include
)

target_link_libraries(exec PRIVATE
    dbase
    domain
    cli
)

target_compile_options(exec PRIVATE ${PROJECT_WARNINGS})
target_compile_options(domain PRIVATE ${PROJECT_WARNINGS})
target_compile_options(cli PRIVATE ${PROJECT_WARNINGS})
target_compile_options(dbase PRIVATE ${PROJECT_WARNINGS})
