#ifndef __UTIL_CHARCONV_HPP
#define __UTIL_CHARCONV_HPP

#include <charconv>
#include <string_view>
#include <ranges>

namespace util
{

void from_chars(const std::string_view str, auto& value)
{
	const char* data = str.data();
	std::from_chars(data, data + str.size(), value);
}

template <typename It>
void from_chars(const std::pair<It, It>& pair, auto& value)
{
	from_chars(std::string_view{ pair.first, pair.second }, value);
}

void from_chars(std::ranges::contiguous_range auto && r, auto& value)
{
	from_chars(std::string_view{ r }, value);
}

template <typename T = int>
T from_chars(const auto& obj)
{
	T value;
	from_chars(obj, value);
	return value;
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