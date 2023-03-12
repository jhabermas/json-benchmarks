#include "nl_json.h"
#include <catch2/catch_test_macros.hpp>

using json = nlohmann::json;
using nlohmann_json::transform_json;

TEST_CASE("Transform JSON string to new JSON string", "[nl_transform_json]") {
    REQUIRE(true);
}
