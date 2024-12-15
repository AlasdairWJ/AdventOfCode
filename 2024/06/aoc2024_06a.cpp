#include <iostream>
#include <set>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

using util::Point;

void turn_right(Point& p)
{
	std::tie(p.x, p.y) = std::make_pair(-p.y, p.x);
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	const auto [start_x, start_y] = grid.find('^');

	std::set<Point> history;
	Point p{ start_x, start_y}, delta{ 0, -1 };

	for (;;)
	{
		history.insert(p);

		Point q = p + delta;

		if (!grid.in_bounds(q.x, q.y))
			break;

		if (grid[q.x, q.y] == '#')
		{
			turn_right(delta);
			q = p + delta;
		}

		p = q;
	}

	std::cout << history.size();
}