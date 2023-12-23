#include <iostream>
#include <string> // std::getline
#include <vector>
#include <set>

#include "util/charconv.hpp" // util::from_chars
#include "util/geometry.hpp"

using Point = util::Point;

constexpr Point directions[]{
	Point{ 1, 0 },
	Point{ 0, 1 },
	Point{ -1, 0 },
	Point{ 0, -1 }
};

int main(const int argc, const char* argv[])
{
	int stepTarget = 64;

	if (argc >= 2)
	{
		if (!util::from_chars(argv[1], stepTarget))
			return 1;
	}

	std::vector<std::string> grid;

	std::set<Point> points;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto ix = line.find('S');
		if (ix != std::string::npos)
		{
			line[ix] = '.';

			points.emplace(
				static_cast<int>(ix),
				static_cast<int>(grid.size())
			);
		}

		grid.push_back(line);
	}

	const int size = static_cast<int>(grid.size());

	for (int steps = 0; steps < stepTarget; steps++)
	{
		decltype(points) nextPoints;

		for (const auto& p : points)
		{
			for (const auto& d : directions)
			{
				const Point nextP = d + p;

				if (
					nextP.x >= 0 && 
					nextP.y >= 0 && 
					nextP.x < size && 
					nextP.y < size &&
					grid[nextP.y][nextP.x] != '#'
				)
				{
					nextPoints.insert(nextP);
				}
			}
		}

		points.swap(nextPoints);
	}

	std::cout << points.size();
}