
add_library(domain
    src/contact_repository.cpp
)

target_include_directories(domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(domain PUBLIC
    dbase
)