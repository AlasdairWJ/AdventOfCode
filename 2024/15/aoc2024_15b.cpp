#include <iostream>
#include <string>
#include <vector>
#include <ranges>

#include "../../util/point.hpp"

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

bool can_move_vertical(const auto& lines, const Point& p, int dy)
{
	const char above = lines[p.y + dy][p.x];

	switch (above)
	{
	case Wall:
		return false;

	case CrateLeft:
		return
			can_move_vertical(lines, Point{ p.x, p.y + dy }, dy) &&
			can_move_vertical(lines, Point{ p.x + 1, p.y + dy }, dy);

	case CrateRight:
		return
			can_move_vertical(lines, Point{ p.x, p.y + dy }, dy) &&
			can_move_vertical(lines, Point{ p.x - 1, p.y + dy }, dy);

	case Empty:
	default:
		return true;
	}
}

void move_vertical(auto& lines, const Point& p, int dy)
{
	const char above = lines[p.y + dy][p.x];

	switch (above)
	{
	case CrateLeft:
		move_vertical(lines, Point{ p.x, p.y + dy }, dy);
		move_vertical(lines, Point{ p.x + 1, p.y + dy }, dy);
		break;

	case CrateRight:
		move_vertical(lines, Point{ p.x, p.y + dy }, dy);
		move_vertical(lines, Point{ p.x - 1, p.y + dy }, dy);
		break;

	default:
		break;
	}

	lines[p.y + dy][p.x] = lines[p.y][p.x];
	lines[p.y][p.x] = Empty;
}

int main(int _, const char*[])
{
	std::vector<std::string> lines;

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		auto& l = lines.emplace_back();

		for (const char c : line)
		{
			switch (c)
			{
			case Crate:
				l.push_back(CrateLeft);
				l.push_back(CrateRight);
				break;
			case Robot:
				l.push_back(Robot);
				l.push_back(Empty);
				break;
			default:
				l.push_back(c);
				l.push_back(c);
				break;
			}
		}
	}

	Point robot{};

	for (auto [ix, line] : lines | std::views::enumerate)
	{
		if (const auto pos = line.find(Robot); pos != std::string::npos)
		{
			robot.x = static_cast<int>(pos);
			robot.y = static_cast<int>(ix);
			break;
		}
	}

	for (std::string line; std::getline(std::cin, line); )
	{
		for (const char c : line)
		{
			const Point d = direction_from_char(c);
			
			if (d.x != 0)
			{
				// Horizontal movement

				const Point neighbour = robot + d;

				if (lines[neighbour.y][neighbour.x] != Wall)
				{
					Point q = neighbour;

					while (lines[q.y][q.x] == CrateLeft || lines[q.y][q.x] == CrateRight)
					{
						q += d;
						q += d;
					}

					if (lines[q.y][q.x] == Empty)
					{
						while (q != neighbour)
						{
							lines[q.y][q.x] = lines[q.y - d.y][q.x - d.x];
							q -= d;
						}

						lines[q.y][q.x] = Robot;
						lines[robot.y][robot.x] = Empty;

						robot = neighbour;
					}
				}

			}
			else
			{
				// Vertical movement

				if (can_move_vertical(lines, robot, d.y))
				{
					move_vertical(lines, robot, d.y);
					robot += d;
				}
			}
		}
	}

	int total = 0;

	for (auto [index, line] : lines | std::views::enumerate)
	{
		auto pos = line.find(CrateLeft);

		while (pos != std::string::npos)
		{
			total += 100 * static_cast<int>(index) + static_cast<int>(pos);

			pos = line.find(CrateLeft, pos + 1);
		}
	}

	std::cout << total;
}