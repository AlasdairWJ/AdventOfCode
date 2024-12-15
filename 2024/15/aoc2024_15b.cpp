#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/Grid.hpp"
#include "../../util/Point.hpp"

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
	case '^': return Point{ 0, -1 };
	case 'v': return Point{ 0, 1 };
	case '<': return Point{ -1, 0 };
	case '>': return Point{ 1, 0 };
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

	const auto [rx, ry] = grid.find(Robot);
	Point robot{ rx, ry };

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const char c : line)
		{
			const Point d = direction_from_char(c);
			
			if (d.x != 0)
			{
				// Horizontal movement

				const Point neighbour = robot + d;

				if (grid[neighbour.x, neighbour.y] != Wall)
				{
					Point q = neighbour;

					while (grid[q.x, q.y] == CrateLeft || grid[q.x, q.y] == CrateRight)
					{
						q += d,
						q += d;
					}

					if (grid[q.x, q.y] == Empty)
					{
						while (q != neighbour)
						{
							grid[q.x, q.y] = grid[q.x - d.x, q.y - d.y];
							q -= d;
						}

						grid[q.x, q.y] = Robot;
						grid[robot.x, robot.y] = Empty;

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