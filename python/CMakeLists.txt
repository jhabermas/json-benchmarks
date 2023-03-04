find_package(pybind11 REQUIRED)

pybind11_add_module(_hello def_hello.cpp)

target_link_libraries(_hello PRIVATE hello)

target_include_directories(_hello PRIVATE ${CMAKE_SOURCE_DIR}/include)

install(TARGETS _hello DESTINATION ${CMAKE_SOURCE_DIR}/python/hello)