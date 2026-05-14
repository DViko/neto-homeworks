add_library(cli
    src/client_cli.cpp
)

target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/domain/include
)

target_link_libraries(cli PUBLIC
    domain
)