cmake_minimum_required(VERSION 3.15)
project(hello VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_TIDY NAMES "clang-tidy" "clang-tidy-14")
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(python)
add_subdirectory(app)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)