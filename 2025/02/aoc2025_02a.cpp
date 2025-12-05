#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <ranges>
#include <cmath>

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
};

int ndigits(const int x)
{
	return static_cast<int>(std::log10(x)) + 1;
}

i64 concat(const i64 x, const i64 y)
{
	return x * Tens[ndigits(y)] + y;
}

int main()
{
	std::string line;
	std::getline(std::cin, line);

	i64 total = 0;

	for (auto && r : line | std::views::split(','))
	{
		const std::string_view str{ r.begin(), r.end() };
		const auto ix = str.find('-');

		const auto lower_str = str.substr(0, ix);
		const auto upper_str = str.substr(ix + 1);

		const i64 lower = *util::from_chars<i64>(lower_str);
		const i64 upper = *util::from_chars<i64>(upper_str);

		const auto half_lower_str = lower_str.substr(0, lower_str.size() / 2);
		const auto half_lower = *util::from_chars<i64>(half_lower_str);
		
		const auto half_upper_str = upper_str.substr(0, upper_str.size() / 2);
		const auto half_upper = *util::from_chars<i64>(half_upper_str);
		
		int count = 0;

		for (i64 x = half_lower; x <= half_upper; x++)
		{
			const i64 y = concat(x, x);

			if (lower <= y && y <= upper)
			{
				total += y;
				count++;
			}
		}
	}

	std::cout << total;
}

