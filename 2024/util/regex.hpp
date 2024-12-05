#ifndef __UTIL_REGEX_HPP
#define __UTIL_REGEX_HPP

#include <regex>
#include <string_view>

namespace util
{

using sv_sub_match = std::sub_match<std::string_view::const_iterator>;
using sv_match = std::match_results<std::string_view::const_iterator>;
using sv_regex_iterator = std::regex_iterator<std::string_view::const_iterator>;
using sv_regex_token_iterator = std::regex_token_iterator<std::string_view::const_iterator>;

auto all_matches(const std::string_view line, const std::regex& pattern)
{
	return std::ranges::subrange(
		sv_regex_iterator(line.begin(), line.end(), pattern),
		sv_regex_iterator()
	);
}

} // util

#endif // __UTIL_REGEX_HPP