#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/point.hpp"

using util::Point;

constexpr char Wall = '#';
constexpr char Robot = '@';
constexpr char Crate = 'O';
constexpr char Empty = '.';

Point direction_from_char(const char c)
{
	switch (c)
	{
	case '^': return Point{ 0, -1 };
	case 'v': return Point{ 0, 1 };
	case '<': return Point{ -1, 0 };
	case '>': return Point{ 1, 0 };
	default: return Point{};
	}
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		lines.push_back(line);

	Point robot{};

	for (auto [ix, line] : lines | std::views::enumerate)
	{
		if (const auto pos = line.find(Robot); pos != std::string::npos)
		{
			robot.x = static_cast<int>(pos);
			robot.y = static_cast<int>(ix);
			line[pos] = Empty;
			break;
		}
	}

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const char c : line)
		{
			const Point d = direction_from_char(c);
			
			const Point neighbour = robot + d;
			char n = lines[neighbour.y][neighbour.x];

			if (n != Wall)
			{
				Point q = neighbour;
				const bool move_crates = (n == Crate);

				if (move_crates)
				{
					do
					{
						q += d;
						n = lines[q.y][q.x];
					}
					while (n == Crate);
				}

				if (n == Empty)
				{
					if (move_crates)
					{
						lines[neighbour.y][neighbour.x] = Empty;
						lines[q.y][q.x] = Crate;
					}

					robot = neighbour;
				}
			}
		}
	}

	int total = 0;

	for (auto [index, line] : lines | std::views::enumerate)
	{
		auto pos = line.find(Crate);

		while (pos != std::string::npos)
		{
			total += 100 * static_cast<int>(index) + static_cast<int>(pos);

			pos = line.find(Crate, pos + 1);
		}
	}

	std::cout << total;
}