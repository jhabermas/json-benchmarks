add_executable(jsb
        main.cpp
        boost_json.h
        glaze_json.h
        nl_json.h
        simd_json.h
)

target_link_libraries(jsb
    PRIVATE
        Boost::json
        Boost::program_options
        fmt::fmt
        glaze::glaze
        nlohmann_json::nlohmann_json
        simdjson::simdjson
)

install(TARGETS jsb DESTINATION ${CMAKE_SOURCE_DIR}/bin)