#include <catch2/catch_test_macros.hpp>
#include "hello/hello.h"

TEST_CASE("say_hello replies hello world", "[hello_tag]") {
    REQUIRE(hello::say_hello("world") == "Hello world");
}