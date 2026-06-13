#pragma once


#include <stdexcept>
#include <string>

template <class E>
[[noreturn]] inline void Throw(const E& e) noexcept(false)
{
    throw e;
}
