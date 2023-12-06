#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <cstdint>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/numeric.hpp" // util::solve_quadratic

int main(int _, const char*[])
{
	int64_t time{}, distance{};

	for (int64_t* pValue : { &time, &distance })
	{
		std::string line;
		std::getline(std::cin, line);

		std::string value_str;

		std::ranges::copy(
			// god knows why i can't construct a string directly from this
			line | std::views::split(' ') | std::views::drop(1) | std::views::join,
			std::back_inserter(value_str)
		);

		if (int64_t value; util::from_chars(value_str, value))
			*pValue = value;
	}

	double largest_time, smallest_time;
	if (util::solve_quadratic<double>(1, -time, distance, smallest_time, largest_time))
		std::cout << static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
}