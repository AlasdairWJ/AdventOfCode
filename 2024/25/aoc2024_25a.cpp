#include <iostream>
#include <string>
#include <array>
#include <ranges>

#include "../../util/Grid.hpp"

using Values = std::array<int, 5>;

Values values_from_grid(const auto& grid, const bool is_lock)
{
	Values values{};

	for (int x = 0; x < grid.width(); x++)
	{
		int y;
		if (is_lock)
		{
			y = 0;
			while (y < grid.height() && grid[x, y] == '#')
				y++;
		}
		else
		{
			y = grid.height() - 1;
			while (y >= 0 && grid[x, y] == '#')
				y--;

			y = grid.height() - y - 1;
		}
		values[x] = y - 1;
	}

	return values;
}

int main(int _, const char*[])
{
	std::vector<Values> locks;
	std::vector<Values> keys;

	while (std::cin)
	{
		util::Grid grid;
		std::cin >> grid;

		const bool is_lock = (grid[0, 0] == '#');
		const Values values = values_from_grid(grid, is_lock);

		if (is_lock)
			locks.push_back(values);
		else
			keys.push_back(values);
	}

	int count = 0;

	for (const auto& [key, lock] : std::views::cartesian_product(keys, locks))
	{
		bool fit = true;

		for (const auto& [a, b] : std::views::zip(key, lock))
		{
			if (a + b > 5)
			{
				fit = false;
				break;
			}
		}

		if (fit)
			count++;
	}

	std::cout << count;
}
