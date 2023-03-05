#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/json.hpp>

using namespace boost::json;

std::vector<std::string> generate_json_array(int n) {
    std::vector<std::string> json_array;
    for (int i = 0; i < n; i++) {
        object obj = {
            {"id", boost::uuids::to_string(boost::uuids::random_generator()())},
            {"string", "hello world"},
            {"number", rand() % 201 - 100},
            {"boolean", rand() % 2 == 0},
            {"null", nullptr},
            {"array", {1, 2, 3, 4, 5, 6, 7, i}},
            {"object", {{"key", i}}},
            {"timestamp", static_cast<int>(std::time(nullptr))}
        };
        std::string json_str = serialize(obj);
        json_array.push_back(json_str);
    }
    return json_array;
}

