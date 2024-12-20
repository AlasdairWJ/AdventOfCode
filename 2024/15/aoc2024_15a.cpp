#include <iostream>
#include <ranges>

#include "../../util/Grid.hpp"

using util::Point;

constexpr char Wall = '#';
constexpr char Robot = '@';
constexpr char Crate = 'O';
constexpr char Empty = '.';

Point direction_from_char(const char c)
{
	switch (c)
	{
	case '^': return util::Up;
	case 'v': return util::Down;
	case '<': return util::Left;
	case '>': return util::Right;
	default: return Point{};
	}
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	Point robot = grid.find(Robot);

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const char c : line)
		{
			const Point d = direction_from_char(c);
			
			const Point neighbour = robot + d;
			char n = grid[neighbour];

			if (n != Wall)
			{
				Point q = neighbour;
				const bool move_crates = (n == Crate);

				if (move_crates)
				{
					do
					{
						q += d;
						n = grid[q];
					}
					while (n == Crate);
				}

				if (n == Empty)
				{
					if (move_crates)
						grid[q] = Crate;

					grid[neighbour] = Robot;
					grid[robot] = Empty;

					robot = neighbour;
				}
			}
		}
	}

	int total = 0;

	for (auto [index, row] : grid | std::views::enumerate)
	{
		auto pos = row.find(Crate);

		while (pos != std::string::npos)
		{
			total += 100 * static_cast<int>(index) + static_cast<int>(pos);

			pos = row.find(Crate, pos + 1);
		}
	}

	std::cout << total;
}