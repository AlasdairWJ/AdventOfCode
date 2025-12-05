#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <numeric>

#include "../util/charconv.hpp"

typedef long long i64;

int main()
{
	std::vector<std::pair<i64, i64>> ranges;

	{
		std::string line;
		while (std::getline(std::cin, line), !line.empty())
		{
			const auto ix = line.find('-');
			const auto lower_str = std::string_view{ line }.substr(0, ix);
			const auto upper_str = std::string_view{ line }.substr(ix + 1);

			const i64 lower = *util::parse<i64>(lower_str);
			const i64 upper = *util::parse<i64>(upper_str);
			ranges.emplace_back(lower, upper);
		}
	}

	std::ranges::sort(
		ranges,
		[](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; }
	);

	decltype(ranges)::iterator it = ranges.begin();

	for (auto next = it + 1; next != ranges.end(); ++next)
	{
		if (next->first <= it->second)
		{
			it->second = std::max(it->second, next->second);
		}
		else
		{
			*(++it) = *next;
		}
	}

	std::cout << std::accumulate(
		ranges.begin(),
		it + 1,
		0ll,
		[](const i64 total, const auto& pair)
		{
			return total + (pair.second - pair.first + 1);
		}
	);
}