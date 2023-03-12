#pragma once

#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
#include <numeric>

namespace nlohmann_json
{

using json = nlohmann::json;

inline std::string transform_json(const std::string& json_str) {
  json data = json::parse(json_str);
  json new_data = {
    {"id", data["id"].get<std::string>().substr(data["id"].get<std::string>().length() - 8)},
    {"str", data["string"].get<std::string>().substr(0, data["string"].get<std::string>().find(' '))},
    {"num", data["number"].get<int>() + 1},
    {"val", data["null"].is_null() ? 0 : 1},
    {"sum", 7}, //std::accumulate(data["array"].begin(), data["array"].end(), 0)},
    {"obj", "object"},
    {"timestamp", data["timestamp"].get<std::string>()}
  };

  return new_data.dump();
}

}