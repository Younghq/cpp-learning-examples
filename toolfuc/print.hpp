#pragma once
#include <iostream>

// cout和printf来了都得叫爹
template <typename... Args>
void print(Args... args)
{
    (std::cout << ... << args) << std::endl;
}
