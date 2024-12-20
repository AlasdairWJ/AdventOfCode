#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/Grid.hpp"

using util::Point;

constexpr char Wall = '#';
constexpr char Robot = '@';
constexpr char Crate = 'O';
constexpr char CrateLeft = '[';
constexpr char CrateRight = ']';
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

bool can_move_vertical(const auto& grid, const Point& p, int dy)
{
	const char above = grid[p.x, p.y + dy];

	switch (above)
	{
	case Wall:
		return false;

	case CrateLeft:
		return
			can_move_vertical(grid, Point{ p.x, p.y + dy }, dy) &&
			can_move_vertical(grid, Point{ p.x + 1, p.y + dy }, dy);

	case CrateRight:
		return
			can_move_vertical(grid, Point{ p.x, p.y + dy }, dy) &&
			can_move_vertical(grid, Point{ p.x - 1, p.y + dy }, dy);

	case Empty:
	default:
		return true;
	}
}

void move_vertical(auto& grid, const Point& p, int dy)
{
	const char above = grid[p.x, p.y + dy];

	switch (above)
	{
	case CrateLeft:
		move_vertical(grid, Point{ p.x, p.y + dy }, dy);
		move_vertical(grid, Point{ p.x + 1, p.y + dy }, dy);
		break;

	case CrateRight:
		move_vertical(grid, Point{ p.x, p.y + dy }, dy);
		move_vertical(grid, Point{ p.x - 1, p.y + dy }, dy);
		break;

	default:
		break;
	}

	grid[p.x, p.y + dy] = grid[p.x, p.y];
	grid[p.x, p.y] = Empty;
}

int main(int _, const char*[])
{
	util::Grid initial_grid;
	std::cin >> initial_grid;

	util::Grid grid(2 * initial_grid.width(), initial_grid.height());

	for (int y = 0; y < initial_grid.height(); y++)
	{
		for (int x = 0; x < initial_grid.width(); x++)
		{
			switch (const char c = initial_grid[x, y]; c)
			{
			case Crate:
				grid[2 * x, y] = CrateLeft;
				grid[2 * x + 1, y] = CrateRight;
				break;
			case Robot:
				grid[2 * x, y] = Robot;
				grid[2 * x + 1, y] = Empty;
				break;
			default:
				grid[2 * x, y] = c;
				grid[2 * x + 1, y] = c;
				break;
			}
		}
	}

	Point robot = grid.find(Robot);

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const char c : line)
		{
			const Point d = direction_from_char(c);
			
			if (d.x != 0)
			{
				// Horizontal movement

				const Point neighbour = robot + d;

				if (grid[neighbour] != Wall)
				{
					Point q = neighbour;

					while (grid[q] == CrateLeft || grid[q] == CrateRight)
					{
						q += d,
						q += d;
					}

					if (grid[q] == Empty)
					{
						while (q != neighbour)
						{
							grid[q] = grid[q - d];
							q -= d;
						}

						grid[q] = Robot;
						grid[robot] = Empty;

						robot = neighbour;
					}
				}

			}
			else
			{
				// Vertical movement

				if (can_move_vertical(grid, robot, d.y))
				{
					move_vertical(grid, robot, d.y);
					robot += d;
				}
			}
		}
	}

	int total = 0;

	for (auto [index, row] : grid | std::views::enumerate)
	{
		auto pos = row.find(CrateLeft);

		while (pos != std::string::npos)
		{
			total += 100 * static_cast<int>(index) + static_cast<int>(pos);

			pos = row.find(CrateLeft, pos + 1);
		}
	}

	std::cout << total;
}