#include <iostream>
#include <string>
#include <ranges>
#include <set>
#include <map>

#include "../util/charconv.hpp"
#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"
#include "../../util/separate.hpp"

using util::Point;

#ifdef TEST
constexpr int Size = 7; 
constexpr int Steps = 12; 
#else
constexpr int Size = 71; 
constexpr int Steps = 1024;
#endif

bool find_route(const auto& grid, const Point start, const Point end, std::set<Point>& route)
{
	std::map<Point, int> history;
	history.emplace(start, 0);

	std::set<Point> current;
	current.insert(start);

	int iteration = 0;
	for (; !current.empty() && !current.contains(end); iteration++)
	{
		decltype(current) next;

		for (const auto& p : current)
		{
			for (const auto& d : util::UnitDirections)
			{
				const auto q = p + d;
				if (grid.in_bounds(q.x, q.y) && grid[q.x, q.y] == ' ' && !history.contains(q))
				{
					next.insert(q);
					history.emplace(q, iteration + 1);
				}
			}
		}

		current.swap(next);
	}

	if (current.empty())
		return false;

	for (Point p = end; p != start; iteration--)
	{
		for (const auto& d : util::UnitDirections)
		{
			const auto q = p + d;
			const auto it = history.find(q);
			if (it != history.end() && it->second == iteration - 1)
			{
				p = q;
				route.insert(q);
				break;
			}
		}
	}

	return true;
}

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

	for (const auto [x, y] : blocks | std::views::take(Steps))
		grid[x, y] = '#';

	const Point start{ 0, 0 };
	const Point end{ Size - 1, Size - 1};

	std::set<Point> route;
	find_route(grid, start, end, route);

	for (const auto& p : blocks | std::views::drop(Steps))
	{
		grid[p.x, p.y] = '#';

		if (route.contains(p))
		{
			route.clear();
			
			const bool rerouted = find_route(grid, start, end, route);

			if (!rerouted)
			{
				std::cout << p.x << ',' << p.y;
				return 0;
			}
		}
	}
}