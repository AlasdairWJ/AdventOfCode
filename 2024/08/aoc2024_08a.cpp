#include <iostream>
#include <map>
#include <set>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

using util::Point;

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	std::map<char, std::set<Point>> nodes;

	for (Point p{}; p.y < grid.height(); p.y++)
	{
		for (p.x = 0; p.x < grid.width(); p.x++)
		{
			if (const char c = grid[p]; c != '.')
			{
				nodes[c].insert(p);
			}
		}
	}

	std::set<Point> antinodes;

	for (const auto& [_, node_set] : nodes)
	{
		for (auto it_a = node_set.begin(); it_a != node_set.end(); ++it_a)
		{
			for (auto it_b = std::next(it_a); it_b != node_set.end(); ++it_b)
			{
				const Point d = *it_b - *it_a;

				if (const Point p = *it_a - d; grid.in_bounds(p))
					antinodes.insert(p);

				if (const Point p = *it_b + d; grid.in_bounds(p))
					antinodes.insert(p);
			}
		}
	}

	std::cout << antinodes.size();
}
