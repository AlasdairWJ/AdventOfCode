#ifndef __UTIL_SEPARATE_HPP
#define __UTIL_SEPARATE_HPP

#include <string_view>
#include <array>

namespace util
{

namespace
{
template <std::size_t N, std::size_t I = 0>
void _separate(const std::string_view text, const std::string_view separator, std::array<std::string_view, N>& values)
{
	const std::size_t ix = text.find(separator);
	values[I] = text.substr(0, ix);

	if (ix != std::string_view::npos)
	{
		if (const std::size_t end_ix = ix + separator.size(); end_ix != text.size())
		{
			if constexpr (I + 2 < N)
			{
				_separate<N, I + 1>(text.substr(end_ix), separator, values);
			}
			else
			{
				values[I + 1] = text.substr(end_ix);
			}
		}
	}
}
}

template <std::size_t N = 2>
std::array<std::string_view, N> separate(const std::string_view text, const std::string_view separator = " ")
{
	std::array<std::string_view, N> values{};
	_separate<N>(text, separator, values);
	return values;
}

} // util

#endif // __UTIL_SEPARATE_HPP