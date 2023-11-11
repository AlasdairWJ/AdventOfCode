#ifndef __UTIL_NUMERIC_HPP
#define __UTIL_NUMERIC_HPP

#include "concepts.hpp"

namespace util
{

template <Number T>
int sign(const T& val) { return (T{} < val) - (val < T{}); }

} // util

#endif // __UTIL_NUMERIC_HPP