#include <iostream>
#include <set>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

using util::Point;

void turn_right(Point& p)
{
	std::tie(p.x, p.y) = std::make_pair(-p.y, p.x);
}

bool do_walk(const auto& grid, const Point start_p, std::set<Point>* pLocations = nullptr)
{
	std::set<Point> corners;

	Point p = start_p, delta{ 0, -1 };

	for (;;)
	{
		Point q = p + delta;

		if (!grid.in_bounds(q.x, q.y))
			return false;

		if (grid[q.x, q.y] == '#')
		{
			const auto [_, is_new] = corners.emplace(p);

			if (!is_new)
				return true;

			turn_right(delta);
			q = p + delta;

			if (grid[q.x, q.y] == '#')
			{
				turn_right(delta);
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

	const auto [start_x, start_y] = grid.find('^');

	const Point start_p{ start_x, start_y };

	std::set<Point> locations;
	do_walk(grid, start_p, &locations);

	int count = 0;

	for (const auto [x, y] : locations)
	{
		if (char& c = grid[x, y]; c == '.')
		{
			c = '#';

			if (const bool looped = do_walk(grid, start_p); looped)
				count++;

			c = '.';
		}
	}

	std::cout << count;
}