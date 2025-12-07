#ifndef __UTIL_SEPARATE_HPP
#define __UTIL_SEPARATE_HPP

#include <string_view>
#include <array>

namespace util
{

template <std::size_t N = 2>
constexpr auto separate(const std::string_view text, const std::string_view delim = " ")
{
	static_assert(N >= 2);

	std::array<std::string_view, N> items{};
	
	std::size_t ix = 0, next_ix;
	
	for (std::size_t n = 0; n < N; n++)
	{
		if (n < (N - 1) && (next_ix = text.find(delim, ix)) != std::string_view::npos)
		{
			items[n] = text.substr(ix, next_ix - ix);
			ix = next_ix + delim.size();
		}
		else
		{
			items[n] = text.substr(ix);
			break;
		}
	}

	return items;
}

template <std::size_t N = 2>
constexpr auto separate(const std::string_view text, const char c)
{
	return separate<N>(text, std::string_view{ &c, 1 });
}

} // util

#endif // __UTIL_SEPARATE_HPP