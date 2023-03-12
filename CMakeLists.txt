cmake_minimum_required(VERSION 3.15)
project(json_benchmark VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_TIDY NAMES "clang-tidy" "clang-tidy-14")
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(glaze REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(simdjson REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(cpp)
