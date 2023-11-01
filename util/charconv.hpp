#ifndef __UTIL_CHARCONV_HPP
#define __UTIL_CHARCONV_HPP

#include <charconv>
#include <ranges>
#include <utility>

namespace util
{

template <typename R>
concept Stringy = std::ranges::range<R> && std::is_same_v<std::ranges::range_value_t<R>, char>;

template <typename T> requires (std::is_arithmetic_v<T>)
bool from_chars(Stringy auto && r, T& value)
{
	const char* data = std::ranges::data(r);
	return std::from_chars(data, data + std::ranges::size(r), value).ec == std::errc{};
}

template <typename It, typename T> requires (std::is_arithmetic_v<T>)
bool from_chars(const std::pair<It, It>& pair, T& value)
{
	return from_chars(std::ranges::subrange(pair.first, pair.second), value);
}

} // util

#endif // __UTIL_CHARCONV_HPP