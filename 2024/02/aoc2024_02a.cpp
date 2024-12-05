#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::ranges::sort

#include "../util/charconv.hpp"

bool is_safe(const auto& values)
{
	const bool is_ordered = 
		std::ranges::is_sorted(values, std::less{}) ||
		std::ranges::is_sorted(values, std::greater{});

	if (!is_ordered)
		return false;

	for (const auto [a, b] : values | std::views::adjacent<2>)
		if ((a == b) || std::abs(b - a) > 3)
			return false;

	return true;
}

int main(int _, const char*[])
{
	int count = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto values = line 
			| std::views::split(' ')
			| std::views::transform(util::from_chars_t{})
			| std::ranges::to<std::vector>();

		count += is_safe(values);
	}

	std::cout << count;
}
