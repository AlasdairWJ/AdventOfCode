#include <iostream>
#include <map>
#include <ranges>
#include <numeric>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

using util::Point;

int trail_rating(const auto& grid, const Point start)
{
	std::map<Point, int> locations;
	locations.emplace(start, 1);

	for (char h = '1'; h <= '9' && !locations.empty(); h++)
	{
		decltype(locations) next;

		for (const auto& [l, c] : locations)
		{
			for (const auto& d : util::UnitDirections)
			{
				const auto p = l + d;

				const bool in_bounds = grid.in_bounds(p.x, p.y);

				if (in_bounds && grid[p.x, p.y] == h)
					next[p] += c;
			}
		}

		next.swap(locations);
	}

	auto r = locations | std::views::values;
	return std::accumulate(r.begin(), r.end(), 0);
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
			if (grid[p.x, p.y] == '0')
			{
				total += trail_rating(grid, p);
			}
		}
	}

	std::cout << total;
}
