#include <iostream>
#include <set>
#include <cctype>

#include "../../util/Grid.hpp"

using util::Point;

auto extract_area(auto& grid, const Point& start)
{
	const char letter = grid[start];

	std::set<Point> current;
	current.insert(start);
	
	grid[start] = '.';

	auto all = current;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto p : current)
		{
			for (const auto d : util::UnitDirections)
			{
				const auto q = p + d;

				if (grid.in_bounds(q) && grid[q] == letter)
				{
					grid[q] = '.';
					next.insert(q);
				}

			}
		}

		all.insert(next.begin(), next.end());
		
		current.swap(next);
	}

	return all;
}

int calculate_number_of_sides(const auto& area)
{
	if (area.size() == 1 || area.size() == 2)
		return 4;

	int corners = 0;

	for (const auto p : area)
	{
		const bool up = area.contains(p + Point{ 0, -1 });
		const bool down = area.contains(p + Point{ 0, 1 });
		const bool left = area.contains(p + Point{ -1, 0 });
		const bool right = area.contains(p + Point{ 1, 0 });

		corners += !up && !left;
		corners += up && left && !area.contains(p + Point{ -1, -1 });

		corners += !left && !down;
		corners += left && down && !area.contains(p + Point{ -1, 1 });

		corners += !down && !right;
		corners += down && right && !area.contains(p + Point{ 1, 1 });

		corners += !right && !up;
		corners += right && up && !area.contains(p + Point{ 1, -1 });

	}

	return corners;
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	int total = 0;

	for (Point p{}; p.y < grid.height(); p.y++)
	{
		for (p.x = 0; p.x < grid.width(); p.x++)
		{
			if (const char c = grid[p]; std::isalpha(c))
			{
				const auto area = extract_area(grid, p);
				const auto sides = calculate_number_of_sides(area);

				total += area.size() * sides;
			}
		}
	}

	std::cout << total;
}