
add_library(config
    src/ini_parser.cpp
)

target_include_directories(config PUBLIC
    include
)