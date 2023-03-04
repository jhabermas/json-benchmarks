#include "hello/hello.h"
#include <fmt/format.h>

#include <iostream>

std::string hello::say_hello(std::string_view name)
{
    return fmt::format("Hello {}", name);
}