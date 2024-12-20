#include <iostream>
#include <set>

#include "../../util/Grid.hpp"

using util::Point;

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	const auto start = grid.find('^');

	std::set<Point> history;

	Point p = start;
	Point delta{ 0, -1 };

	for (;;)
	{
		history.insert(p);

		Point q = p + delta;

		if (!grid.in_bounds(q))
			break;

		if (grid[q] == '#')
		{
			delta = delta.turn_right();
			q = p + delta;
		}

		p = q;
	}

	std::cout << history.size();
}