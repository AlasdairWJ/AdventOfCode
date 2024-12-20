#include <iostream>
#include <set>
#include <cctype>

#include "../../util/Grid.hpp"

using util::Point;

auto extract_area(auto& grid, const Point& start)
{
	const char letter = grid[start];

	std::set<Point> current;
	current.insert(start);

	grid[start] = '.';

	auto all = current;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto p : current)
		{
			for (const auto d : util::UnitDirections)
			{
				const auto q = p + d;

				if (grid.in_bounds(q) && grid[q] == letter)
				{
					grid[q] = '.';
					next.insert(q);
				}

			}
		}

		all.insert(next.begin(), next.end());

		current.swap(next);
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

	for (Point p{}; p.y < grid.height(); p.y++)
	{
		for (p.x = 0; p.x < grid.width(); p.x++)
		{
			if (const char c = grid[p]; std::isalpha(c))
			{
				const auto area = extract_area(grid, p);
				const auto perimeter = calculate_perimeter(area);

				total += area.size() * perimeter;
			}
		}
	}

	std::cout << total;
}