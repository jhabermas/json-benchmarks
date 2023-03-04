add_executable(hello_world main.cpp)

target_link_libraries(hello_world PRIVATE hello)

target_include_directories(hello_world PRIVATE ${CMAKE_SOURCE_DIR}/include)
