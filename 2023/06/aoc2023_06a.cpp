#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split, std::view::drop, std::views::zip
#include <vector>

#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/numeric.hpp" // util::solve_quadratic

int main(int _, const char*[])
{
	std::vector<int> races[2];

	for (auto& race : races)
	{
		std::string line;
		std::getline(std::cin, line);

		std::size_t i = 0;
		for (auto && r : line | std::views::split(' ') | std::views::drop(1))
		{
			if (int value; util::from_chars(r, value))
			{
				race.push_back(value);
			}
		}
	}

	int total = 1;

	for (const auto [time, best_distance] : std::views::zip(races[0], races[1]))
	{
		double largest_time, smallest_time;
		if (util::solve_quadratic<double>(1, -time, best_distance, smallest_time, largest_time))
			total *= static_cast<int>(std::ceil(largest_time) - std::floor(smallest_time)) - 1;
	}

	std::cout << total;
}