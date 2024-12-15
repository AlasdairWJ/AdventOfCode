#include <iostream>
#include <set>
#include <cctype>

#include "../../util/Point.hpp"
#include "../../util/Grid.hpp"

using util::Point;

auto extract_area(auto& grid, const int start_x, const int start_y)
{
	const char letter = grid[start_x, start_y];

	std::set<Point> current;
	current.emplace(start_x, start_y);
	grid[start_x, start_y] = '.';

	auto all = current;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto p : current)
		{
			for (const auto d : util::UnitDirections)
			{
				const auto q = p + d;

				const bool in_bounds = grid.in_bounds(q.x, q.y);

				if (in_bounds && grid[q.x, q.y] == letter)
				{
					grid[q.x, q.y] = '.';
					next.insert(q);
				}

			}
		}

		current.swap(next);
		all.insert(current.begin(), current.end());
	}

	return all;
}

int calculate_perimeter(const auto& area)
{
	int total = 0;

	for (const auto p : area)
	{
		for (const auto d : util::UnitDirections)
		{
			if (!area.contains(p + d))
				total++;
		}
	}

	return total;	
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	int total = 0;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (const char c = grid[x, y]; std::isalpha(c))
			{
				const auto area = extract_area(grid, x, y);
				const auto perimeter = calculate_perimeter(area);

				total += area.size() * perimeter;
			}
		}
	}

	std::cout << total;
}