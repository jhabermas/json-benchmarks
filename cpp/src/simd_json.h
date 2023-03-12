#pragma once

#include <simdjson.h>
#include <boost/json.hpp>

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>


namespace simd_json
{

using namespace simdjson;

inline std::string transform_json(const std::string& json_str) {
  dom::parser parser;
  dom::element data = parser.parse(json_str);
  boost::json::value new_data = {
    {"id", data["id"].get_string().value().substr(data["id"].get_string().value().size() - 8)},
    {"str", data["string"].get_string().value().substr(0, data["string"].get_string().value().find(' '))},
    {"num", data["number"].get_int64() + 1},
    {"val", data["null"].is_null() ? 0 : 1},
    {"sum", std::accumulate(data["array"].begin(), data["array"].end(), 0, [](int acc, dom::element v) { return acc + v.get_int64(); })},
    {"obj", "object"},
    {"timestamp", data["timestamp"].get_string().value()}
  };

  // simdjson doesn't provide serialization, so we use it for parsing only, then serialize with boost
  return boost::json::serialize(new_data);
}

}