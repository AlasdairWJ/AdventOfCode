#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "../../util/Geometry.hpp"

using util::Point;

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line); )
		lines.push_back(line);

	std::map<char, std::set<Point>> nodes;

	const int height = static_cast<int>(lines.size());
	const int width = static_cast<int>(lines.front().size());

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (const char c = lines[y][x]; c != '.')
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

				if (const Point p = *it_a - d; p.x >= 0 && p.y >= 0 && p.x < width && p.y < height)
					antinodes.insert(p);

				if (const Point p = *it_b + d; p.x >= 0 && p.y >= 0 && p.x < width && p.y < height)
					antinodes.insert(p);
			}
		}
	}

	std::cout << antinodes.size();
}
