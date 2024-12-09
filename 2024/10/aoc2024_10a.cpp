#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "../../util/Geometry.hpp"

using util::Point;

constexpr Point directions[]{
	Point{ 0, 1 },
	Point{ 0, -1 },
	Point{ 1, 0 },
	Point{ -1, 0 }
};

int trail_heads(const int width, const int height, const auto& lines, const Point start)
{
	std::set<Point> locations{ start };

	for (char h = '1'; h <= '9' && !locations.empty(); h++)
	{
		decltype(locations) next;

		for (const auto& l : locations)
		{
			for (const auto& d : directions)
			{
				const auto p = l + d;

				const bool ok = 
					(p.x >= 0) && 
					(p.y >= 0) && 
					(p.x < width) && 
					(p.y < height) && 
					(lines[p.y][p.x] == h);

				if (ok)
					next.insert(p);
			}
		}

		next.swap(locations);
	}

	return locations.size();
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line); line)
		lines.push_back(line);

	const int height = static_cast<int>(lines.size());
	const int width = static_cast<int>(lines.front().size());

	int total = 0;

	for (Point p{}; p.y < height; p.y++)
	{
		for (p.x = 0; p.x < width; p.x++)
		{
			if (lines[p.y][p.x] == '0')
			{
				total += trail_heads(width, height, lines, p);
			}
		}
	}

	std::cout << total;
}
