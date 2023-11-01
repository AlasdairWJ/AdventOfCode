#ifndef __UTIL_NUMERIC_HPP
#define __UTIL_NUMERIC_HPP

#include <type_traits>

namespace util
{

template <typename T> requires (std::is_arithmetic_v<T>)
int sign(const T& val) { return (T{} < val) - (val < T{}); }

} // util

#endif // __UTIL_NUMERIC_HPP