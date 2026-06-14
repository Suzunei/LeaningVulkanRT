#pragma once


#include <stdexcept>
#include <string>

template <class E>
inline void Throw(const E& e) noexcept(false)
{
    throw e;
}
