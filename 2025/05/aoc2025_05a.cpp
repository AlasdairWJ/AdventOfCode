#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

#include "../util/charconv.hpp"

typedef long long i64;

int main()
{
	std::vector<std::pair<i64, i64>> ranges;
	std::vector<i64> ingredients;

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

		while (std::getline(std::cin, line))
			ingredients.push_back(util::parse<i64>(line));
	}

	std::cout << std::ranges::count_if(
		ingredients,
		[&](const i64 x) {
			return std::ranges::any_of(
				ranges,
				[=](const auto& range)
				{
					return range.first <= x && x <= range.second;
				}
			);
		}
	);
}