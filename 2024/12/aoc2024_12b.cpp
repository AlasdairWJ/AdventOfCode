#include <iostream>
#include <set>
#include <cctype>

#include "../../util/Point.hpp"
#include "../../util/Grid.hpp"

using util::Point;

auto extract_area(auto& grid, const int start_x, const int start_y)
{
	const char letter = grid[start_x, start_y];

	std::set<Point> current;
	current.emplace(start_x, start_y);
	grid[start_x, start_y] = '.';

	auto all = current;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto p : current)
		{
			for (const auto d : util::UnitDirections)
			{
				const auto q = p + d;

				const bool in_bounds = grid.in_bounds(q.x, q.y);

				if (in_bounds && grid[q.x, q.y] == letter)
				{
					grid[q.x, q.y] = '.';
					next.insert(q);
				}

			}
		}

		current.swap(next);
		all.insert(current.begin(), current.end());
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

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (const char c = grid[x, y]; std::isalpha(c))
			{
				const auto area = extract_area(grid, x, y);
				const auto sides = calculate_number_of_sides(area);

				total += area.size() * sides;
			}
		}
	}

	std::cout << total;
}