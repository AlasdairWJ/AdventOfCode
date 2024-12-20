#include <iostream>
#include <set>

#include "../../util/Grid.hpp"

using util::Point;

bool do_walk(const auto& grid, const Point start, std::set<Point>* pLocations = nullptr)
{
	std::set<Point> corners;

	Point p = start;
	Point delta{ 0, -1 };

	for (;;)
	{
		Point q = p + delta;

		if (!grid.in_bounds(q))
			return false;

		if (grid[q] == '#')
		{
			const auto [_, is_new] = corners.emplace(p);

			if (!is_new)
				return true;

			delta = delta.turn_right();
			q = p + delta;

			if (grid[q] == '#')
			{
				delta = delta.turn_right();
				q = p + delta;
			}
		}

		p = q;

		if (pLocations != nullptr)
		{
			pLocations->insert(p);
		}
	}
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	const Point start = grid.find('^');

	std::set<Point> locations;
	do_walk(grid, start, &locations);

	int count = 0;

	for (const auto p : locations)
	{
		if (char& c = grid[p]; c == '.')
		{
			c = '#';

			if (const bool looped = do_walk(grid, start); looped)
				count++;

			c = '.';
		}
	}

	std::cout << count;
}