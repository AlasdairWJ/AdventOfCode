#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::ranges::sort

#include "../../util/charconv.hpp"

bool is_safe(const auto& values)
{
	const bool is_asc = std::ranges::is_sorted(values, std::less{});
	const bool is_desc = std::ranges::is_sorted(values, std::greater{});

	bool is_adj = true;

	for (const auto [a, b] : values | std::views::adjacent<2>)
		is_adj &= (a != b) && std::abs(b - a) <= 3;

	return is_adj && (is_asc | is_desc);
}

bool is_almost_safe(auto values)
{
	if (is_safe(values))
		return true;

	int previous = values.front();
	values.erase(values.begin());

	for (int& value : values)
	{
		if (is_safe(values))
			return true;

		std::swap(value, previous);
	}

	return is_safe(values);
}

int main(int _, const char*[])
{
	int count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::vector<int> values;

		for (auto && r : line | std::views::split(' '))
			util::from_chars(r, values.emplace_back());

		count += is_almost_safe(values);
	}

	std::cout << count;
}
