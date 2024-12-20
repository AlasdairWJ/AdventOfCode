#include <iostream>
#include <string>
#include <ranges>
#include <set>

#include "../util/charconv.hpp"
#include "../../util/Grid.hpp"
#include "../../util/separate.hpp"

using util::Point;

#ifdef TEST
constexpr int Size = 7; 
constexpr int Steps = 12; 
#else
constexpr int Size = 71; 
constexpr int Steps = 1024;
#endif

int main(int _, const char*[])
{
	util::Grid grid(Size, Size);

	std::vector<Point> blocks;
	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [x_str, y_str] = util::separate(line, ",");
		Point p;
		util::from_chars(x_str, p.x);
		util::from_chars(y_str, p.y);
		blocks.push_back(p);
	}

	for (const auto& p : blocks | std::views::take(Steps))
		grid[p] = '#';

	const Point end{ Size - 1, Size - 1};

	std::set<Point> current;
	current.insert(Point{ 0, 0 });

	int iteration = 0;
	for (; !current.contains(end); iteration++)
	{
		decltype(current) next;

		for (const auto& p : current)
		{
			for (const auto& d : util::UnitDirections)
			{
				if (const auto q = p + d; grid.in_bounds(q) && grid[q] == ' ')
				{
					next.insert(q);
					grid[q] = '#';
				}
			}
		}

		current.swap(next);
	}

	std::cout << iteration;
}