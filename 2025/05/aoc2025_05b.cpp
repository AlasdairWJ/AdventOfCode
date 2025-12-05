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

			const i64 lower = util::parse<i64>(lower_str);
			const i64 upper = util::parse<i64>(upper_str);
			ranges.emplace_back(lower, upper);
		}
	}

	std::ranges::sort(
		ranges,
		[](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; }
	);

	std::vector<std::pair<i64, i64>> new_ranges;
	decltype(new_ranges)::iterator end_it;

	for (const auto pair : ranges)
	{
		if (new_ranges.empty())
		{
			new_ranges.push_back(pair);
			end_it = new_ranges.begin();
		}
		else if (pair.first <= end_it->second)
		{
			if (pair.second > end_it->second)
				end_it->second = pair.second;
		}
		else
		{
			end_it = new_ranges.insert(end_it + 1, pair);
		}
	}

	std::cout << std::accumulate(
		new_ranges.begin(),
		new_ranges.end(),
		0ll,
		[](const i64 total, const auto& pair)
		{
			return total + (pair.second - pair.first + 1);
		}
	);
}