#ifndef __UTIL_CHARCONV_HPP
#define __UTIL_CHARCONV_HPP

#include <charconv>
#include <string_view>
#include <expected>

namespace util
{

template <typename T = int>
auto parse(const std::string_view str)
	-> std::expected<T, std::errc> 
{
	T value{};
	const auto [_, ec] = std::from_chars(
		str.data(), str.data() + str.size(), value
	);
	
	if (ec != std::errc{})
		return std::unexpected{ ec };

	return value;
}

} // util

#endif // __UTIL_CHARCONV_HPP