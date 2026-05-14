
include(FetchContent)

FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx.git
    GIT_TAG 7.10.1
)

FetchContent_MakeAvailable(libpqxx)

add_library(dbase
    src/connection.cpp
)

target_include_directories(dbase PUBLIC
    include
)

target_link_libraries(dbase PUBLIC
    pqxx
)