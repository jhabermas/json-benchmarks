find_package(Catch2 REQUIRED)
add_executable(hello_test hello_test.cpp)
target_link_libraries(hello_test PRIVATE Catch2::Catch2WithMain hello)
target_include_directories(hello_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(Catch)
catch_discover_tests(hello_test)