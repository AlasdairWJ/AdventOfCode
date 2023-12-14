#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split, std::view::drop, std::views::join, std::views::zip
#include <vector>
#include <iterator>
#include <algorithm> // std::ranges::copy
#include <cstdint>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/numeric.hpp" // util::solve_quadratic

int main(int _, const char*[])
{
	int64_t values[2];

	for (int64_t& value : values)
	{
		std::string line;
		std::getline(std::cin, line);

		std::string value_str;

		std::ranges::copy(
			// god knows why i can't construct a string directly from this
			line | std::views::split(' ') | std::views::drop(1) | std::views::join,
			std::back_inserter(value_str)
		);

		util::from_chars(value_str, value);
	}

	double largest_time, smallest_time;
	if (util::solve_quadratic<double>(1, -values[0], values[1], smallest_time, largest_time))
		std::cout << static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
}