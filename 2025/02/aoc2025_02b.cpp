#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <cmath>
#include <set>

#include "../util/charconv.hpp"

typedef long long i64;

constexpr i64 Tens[]{
	1ll,
	10ll,
	100ll,
	1000ll,
	10000ll,
	100000ll,
	1000000ll,
	10000000ll,
	100000000ll,
	1000000000ll,
	10000000000ll,
	100000000000ll,
	1000000000000ll,
};

int ndigits(const int x)
{
	return static_cast<int>(std::log10(x)) + 1;
}

i64 repeat(const i64 x, int n)
{
	i64 y = 0;
	
	for (const i64 ten = Tens[ndigits(x)]; n > 0; n--)
		y = y * ten + x;

	return y;
}

int main()
{
	std::string line;
	std::getline(std::cin, line);

	i64 total = 0;

	std::set<i64> solutions;

	for (auto && r : line | std::views::split(','))
	{
		const std::string_view str{ r.begin(), r.end() };
		const auto ix = str.find('-');

		const auto lower_str = str.substr(0, ix);
		const auto upper_str = str.substr(ix + 1);

		const int lower_size = static_cast<int>(lower_str.size());
		const int upper_size = static_cast<int>(upper_str.size());

		const i64 lower = *util::parse<i64>(lower_str);
		const i64 upper = *util::parse<i64>(upper_str);

		for (int d = 1; d <= upper_size / 2; d++)
		{
			const i64 start = Tens[d - 1];
			const i64 end = Tens[d];

			const int min_reps = std::max(2, lower_size / d);
			const int max_reps = upper_size / d;

			for (i64 x = start; x < end; x++)
			{
				for (int reps = min_reps; reps <= max_reps; reps++)
				{
					const auto y = repeat(x, reps);

					if (lower <= y && y <= upper)
					{
						solutions.insert(y);
					}
				}
			}
		}
	}

	std::cout << std::accumulate(solutions.cbegin(), solutions.cend(), i64{});
}

