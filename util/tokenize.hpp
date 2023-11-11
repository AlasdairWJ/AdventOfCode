#ifndef __UTIL_TOKENIZE_HPP
#define __UTIL_TOKENIZE_HPP

#include <regex>
#include <ranges>

#include "concepts.hpp"

namespace util
{

auto tokenize(const String auto& line, const std::regex& re)
{
	return std::ranges::subrange(
		std::sregex_token_iterator(line.begin(), line.end(), re),
		std::sregex_token_iterator()
	);
}

} // util

#endif // __UTIL_TOKENIZE_HPP