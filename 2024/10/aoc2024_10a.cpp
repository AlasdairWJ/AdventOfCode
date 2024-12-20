#include <iostream>
#include <set>

#include "../../util/Grid.hpp"

using util::Point;

int trail_heads(const auto& grid, const Point start)
{
	std::set<Point> locations{ start };

	for (char h = '1'; h <= '9' && !locations.empty(); h++)
	{
		decltype(locations) next;

		for (const auto& p : locations)
		{
			for (const auto& d : util::UnitDirections)
			{
				const auto q = p + d;

				const bool in_bounds = grid.in_bounds(q);

				if (in_bounds && grid[q] == h)
					next.insert(q);
			}
		}

		next.swap(locations);
	}

	return locations.size();
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
			if (grid[p] == '0')
			{
				total += trail_heads(grid, p);
			}
		}
	}

	std::cout << total;
}
