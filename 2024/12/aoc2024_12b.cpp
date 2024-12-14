#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cctype>

#include "../../util/point.hpp"

using util::Point;

constexpr Point directions[]{
	Point{ 1, 0 },
	Point{ -1, 0 },
	Point{ 0, 1 },
	Point{ 0, -1 }
};

auto extract_area(
	const int width, 
	const int height,
	auto& lines, 
	const int start_x, 
	const int start_y
)
{
	const char letter = lines[start_y][start_x];

	std::set<Point> current;
	current.emplace(start_x, start_y);
	lines[start_y][start_x] = '.';

	auto all = current;

	while (!current.empty())
	{
		decltype(current) next;

		for (const auto p : current)
		{
			for (const auto d : directions)
			{
				const auto q = p + d;

				const bool ok = 
					q.x >= 0 && 
					q.y >= 0 &&
					q.x < width &&
					q.y < height &&
					lines[q.y][q.x] == letter;

				if (ok)
				{
					lines[q.y][q.x] = '.';
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
	std::vector<std::string> lines;

	for (std::string line; std::cin >> line; )
		lines.push_back(line);

	const int height = static_cast<int>(lines.size());
	const int width = static_cast<int>(lines.front().size());

	int total = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const char c = lines[y][x];

			if (std::isalpha(c))
			{
				const auto area = extract_area(width, height, lines, x, y);
				const auto sides = calculate_number_of_sides(area);

				total += area.size() * sides;
			}
		}
	}

	std::cout << total;
}