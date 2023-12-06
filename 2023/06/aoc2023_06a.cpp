#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <cmath>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/numeric.hpp" // util::solve_quadratic

const auto non_empty = [](auto && r) { return !r.empty(); };

struct Race
{
	int time, distance;
};

int main(int _, const char*[])
{
	std::vector<Race> races;

	for (const auto member : { &Race::time, &Race::distance })
	{
		std::string line;
		std::getline(std::cin, line);

		std::size_t i = 0;
		for (auto && r : line | std::views::split(' ') | std::views::drop(1) | std::views::filter(non_empty))
		{
			if (int value; util::from_chars(r, value))
			{
				if (i == races.size())
					races.emplace_back();

				races[i++].*member = value;
			}
		}
	}

	int total = 1;

	for (const auto [time, best_distance] : races)
	{
		double largest_time, smallest_time;
		if (util::solve_quadratic<double>(1, -time, best_distance, smallest_time, largest_time))
			total *= static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
	}

	std::cout << total;
}