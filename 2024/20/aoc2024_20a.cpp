#include <iostream>
#include <string>
#include <ranges>
#include <set>
#include <map>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

using util::Point;

constexpr char Empty = '.';
constexpr char Wall = '#';
constexpr char Start = 'S';
constexpr char End = 'E';

constexpr int CheatTime = 2;
constexpr int MinimumTimeSave = 100;

auto find_route(auto grid, const Point start, const Point end)
{
	std::map<Point, int> route;
	route.emplace(start, 0);

	Point p = start;

	for (int step = 1; p != end; step++)
	{
		grid[p.x, p.y] = Wall;
		
		for (const auto d : util::UnitDirections)
		{
			const auto q = p + d;
			if (grid.in_bounds(q.x, q.y) && grid[q.x, q.y] == Empty)
			{
				p = q;
				route.emplace(q, step);
				break;
			}
		}
	}

	return route;
}

int mh_distance(const Point& p, const Point& q)
{
	return std::abs(p.x - q.x) + std::abs(p.y - q.y);
}

int find_cheat_count(const std::map<Point, int>& route)
{
	const int max_distance = route.size();

	int cheat_count = 0;

	for (auto it_a = route.begin(); it_a != route.end(); ++it_a)
	{
		for (auto it_b = std::next(it_a); it_b != route.end(); ++it_b)
		{
			const auto d = mh_distance(it_a->first, it_b->first);

			if (d == CheatTime)
			{
				const int time_saved = std::abs(it_b->second - it_a->second) - CheatTime;
				
				if (time_saved >= MinimumTimeSave)
					cheat_count++;
			}
		}
	}

	return cheat_count;
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	const auto [start_x, start_y] = grid.find(Start);
	const auto [end_x, end_y] = grid.find(End);

	grid[start_x, start_y] = Empty;
	grid[end_x, end_y] = Empty;

	const Point start{ start_x, start_y };
	const Point end{ end_x, end_y };

	const auto route = find_route(grid, start, end);

	std::cout << find_cheat_count(route);
}