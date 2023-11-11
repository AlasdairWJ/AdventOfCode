#ifndef __UTIL_CHARCONV_HPP
#define __UTIL_CHARCONV_HPP

#include <charconv>
#include <ranges>
#include <utility>

#include "concepts.hpp"

namespace util
{

bool from_chars(String auto && r, Number auto& value)
{
	const char* data = std::ranges::data(r);
	return std::from_chars(data, data + std::ranges::size(r), value).ec == std::errc{};
}

template <typename It>
bool from_chars(const std::pair<It, It>& pair, Number auto& value)
{
	return from_chars(std::ranges::subrange(pair.first, pair.second), value);
}

} // util

#endif // __UTIL_CHARCONV_HPP