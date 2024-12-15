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

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (const char c = grid[x, y]; c != '.')
			{
				nodes[c].emplace(x, y);
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

				if (const Point p = *it_a - d; grid.in_bounds(p.x, p.y))
					antinodes.insert(p);

				if (const Point p = *it_b + d; grid.in_bounds(p.x, p.y))
					antinodes.insert(p);
			}
		}
	}

	std::cout << antinodes.size();
}
