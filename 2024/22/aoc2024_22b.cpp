#include <iostream>
#include <array>
#include <set>
#include <map>
#include <algorithm>
#include <ranges>

typedef long long int64;

constexpr int64 Limit = (1ll << 24) - 1;

constexpr void mix(int64& value, const int64 with)
{
	value ^= with;
}

constexpr void prune(int64& value)
{
	value &= Limit;
}

constexpr int64 next(int64 value)
{
	mix(value, value << 6);
	prune(value);
	mix(value, value >> 5);
	prune(value);
	mix(value, value << 11);
	prune(value);
	return value;
}

void shift_down(auto& values)
{
	std::copy(
		std::next(values.begin()),
		values.end(),
		values.begin()
	);
}

int main(int, const char*[])
{
	std::map<std::array<int, 4>, int64> bananas_sold;

	for (int64 value; std::cin >> value; )
	{
		std::set<std::array<int, 4>> checked_diffs;

		std::array<int, 4> diffs{};

		int64 prev = value;
		int prev_price = static_cast<int>(prev % 10);

		for (int n = 0; n < 2000; n++)
		{
			const int64 current = next(prev);
			const int current_price = static_cast<int>(current % 10);

			const int price_difference = current_price - prev_price;

			if (n >= 4)
				shift_down(diffs);

			diffs[std::min(3, n)] = price_difference;			

			if (n >= 3)
			{
				if (!checked_diffs.contains(diffs))
				{
					bananas_sold[diffs] += current_price;
					checked_diffs.insert(diffs);
				}
			}

			prev = current;
			prev_price = current_price;
		}
	}

	auto cmp_by_second = [](const auto& lhs, const auto&rhs) { return lhs.second < rhs.second; };

	auto it = std::ranges::max_element(bananas_sold, cmp_by_second);

	std::cout << it->second;
}
