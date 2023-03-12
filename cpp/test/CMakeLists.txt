add_executable(json_benchmark_test
        boost_json_test.cpp
        nl_json_test.cpp
        simd_json_test.cpp
)

find_package(Catch2 REQUIRED)

target_link_libraries(json_benchmark_test
        PRIVATE
                Catch2::Catch2WithMain
                Boost::json
                glaze::glaze
                nlohmann_json::nlohmann_json
                simdjson::simdjson
)

target_include_directories(json_benchmark_test PRIVATE ${CMAKE_SOURCE_DIR}/cpp/src)

include(Catch)
catch_discover_tests(json_benchmark_test)
