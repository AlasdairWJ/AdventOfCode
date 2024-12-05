#ifndef __UTIL_CHARCONV_HPP
#define __UTIL_CHARCONV_HPP

#include <charconv>
#include <string_view>
#include <ranges>

namespace util
{

template <typename T = int>
T from_chars(const std::string_view str)
{
	T value{};
	const char* data = str.data();
	std::from_chars(data, data + str.size(), value);
	return value;
}

template <typename T = int, typename It>
T from_chars(const std::pair<It, It>& pair)
{
	return from_chars(std::string_view{ pair.first, pair.second });
}

template <typename T = int>
T from_chars(std::ranges::contiguous_range auto && r)
{
	return from_chars(std::string_view{ r });
}


template <typename T = int>
struct from_chars_t
{
	T operator()(auto && value) const
	{
		return from_chars<T>(value);
	}
};

} // util

#endif // __UTIL_CHARCONV_HPP