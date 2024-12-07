#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/separate.hpp"
#include "../util/charconv.hpp"

long long concat(long long value, int x)
{
	int y = 0;
	int n = 0;

	while (x != 0)
	{
		y *= 10;
		y += x % 10;
		x /= 10;
		n++;
	}

	while (n != 0)
	{
		value *= 10;
		value += y % 10;
		y /= 10;
		n--;
	}

	return value;
}

bool test(const long long target, long long current, const auto it, const auto end)
{
	if (it == end)
		return current == target;

	if (current > target)
		return false;

	const int x = *it;

	return 
		test(target, current + x, it + 1, end) ||
		test(target, current * x, it + 1, end) ||
		test(target, concat(current, x), it + 1, end);
}

int main(int _, const char*[])
{
	long long total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [result_str, equation_str] = util::separate(line, ": ");

		const long long result = util::from_chars<long long>(result_str);

		const auto equation = equation_str 
			| std::views::split(' ')
			| std::views::transform(util::from_chars_t{})
			| std::ranges::to<std::vector>();

		if (test(result, 0ll, equation.cbegin(), equation.cend()))
			total += result;
	}

	std::cout << total;
}