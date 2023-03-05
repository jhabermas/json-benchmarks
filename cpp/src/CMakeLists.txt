add_library(hello "")

add_subdirectory(hello)

set(hello_headers
        ${CMAKE_SOURCE_DIR}/include/hello/hello.h
)

target_sources(hello PRIVATE ${hello_headers})

find_package(fmt REQUIRED)

target_link_libraries(hello PUBLIC fmt::fmt)

target_include_directories(hello
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)