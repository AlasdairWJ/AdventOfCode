#ifndef __SEPARATE_HPP
#define __SEPARATE_HPP

#include <string_view>
#include <algorithm>
#include "concepts.hpp"

namespace util
{

struct separate_result
{
	std::string_view left, right;
};

separate_result separate(const String auto& text, const char separator = ' ')
{
	const auto it = std::ranges::find(text, separator);
	const auto end = std::ranges::end(text);

	return separate_result{
		std::string_view{ std::ranges::begin(text), it },
		std::string_view{ it != end ? it + 1 : it, end }
	};
}

separate_result separate(const String auto& text, String auto && separator)
{
	const auto [foundBegin, foundEnd] = std::ranges::search(text, separator);

	return separate_result{
		std::string_view{
			std::begin(text),
			foundBegin
		},
		std::string_view{
			foundEnd != std::end(text) ? foundEnd + 1 : std::end(text),
			std::end(text)
		}
	};
}

} // util

#endif // __SEPARATE_HPP