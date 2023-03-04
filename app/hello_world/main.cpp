#include <iostream>
#include <hello/hello.h>

int main()
{
    std::cout << hello::say_hello("world") << std::endl;
    return 0;
}
