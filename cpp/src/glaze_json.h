#pragma once

#include <glaze/glaze.hpp>

#include <chrono>
#include <iostream>
#include <string>

struct internal_t
{
    int key;
};

struct data_t
{
  std::string id;
  std::string str;
  int num;
  bool boolean;
  std::unique_ptr<int> val;
  std::array<int, 8> sum;
  internal_t obj;
  std::string timestamp;
};

template <>
struct glz::meta<internal_t> {
   using T = internal_t;
   static constexpr auto value = glz::object(
      "key", &T::key
   );
};

template <>
struct glz::meta<data_t> {
   using T = data_t;
   static constexpr auto value = glz::object(
      "id", &T::id,
      "string", &T::str,
      "number", &T::num,
      "boolean", &T::boolean,
      "null", &T::val,
      "array", &T::sum,
      "object", &T::obj,
      "timestamp", &T::timestamp
   );
};
/*
template <>
struct glz::meta<Thing> {
   static constexpr auto value = object(
      "i", [](auto&& self) -> auto& { return self.subclass.i; }
   );
};
*/

namespace glaze_json
{

inline std::string transform_json(const std::string& json_str) {

    auto data = glz::read_json<data_t>(json_str);
    std::string buffer = glz::write_json(data);
    return buffer;
}

}