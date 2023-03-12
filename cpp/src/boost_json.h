#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/json.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>

namespace boost_json
{

using namespace boost::json;

inline std::vector<std::string> generate_json(int n) {
    std::vector<std::string> json_array;
    std::time_t t = std::time(nullptr);
    for (int i = 0; i < n; i++) {
        object obj = {
            {"id", boost::uuids::to_string(boost::uuids::random_generator()())},
            {"string", "hello world"},
            {"number", rand() % 201 - 100},
            {"boolean", rand() % 2 == 0},
            {"null", nullptr},
            {"array", {1, 2, 3, 4, 5, 6, 7, i}},
            {"object", {{"key", i}}},
            {"timestamp", std::asctime(std::localtime(&t))}
        };
        std::string json_str = serialize(obj);
        json_array.push_back(json_str);
    }
    return json_array;
}

inline std::string transform_json(const std::string& jsonStr) {
  value data = parse(jsonStr);
  object new_data = {
    {"id", data.at("id").as_string()}, //.substr(data.at("id").as_string().size() - 8)},
    {"str", data.at("string").as_string()}, //.substr(0, data.at("string").as_string().find(' '))},
    {"num", data.at("number").as_int64() + 1},
    {"val", data.at("null").is_null() ? 0 : 1},
    {"sum", std::accumulate(data.at("array").as_array().begin(), data.at("array").as_array().end(), 0, [](int acc, const value& v) { return acc + v.as_int64(); })},
    {"obj", "object"},
    {"timestamp", data.at("timestamp").as_string()}
  };

  return serialize(new_data);
}

}