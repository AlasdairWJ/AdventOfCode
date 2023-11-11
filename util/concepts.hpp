#ifndef __CONCEPTS_HPP
#define __CONCEPTS_HPP

#include <type_traits>
#include <ranges>

namespace util
{

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <typename R>
concept String = std::ranges::contiguous_range<R> && std::is_same_v<std::ranges::range_value_t<R>, char>;

}

#endif // __CONCEPTS_HPP