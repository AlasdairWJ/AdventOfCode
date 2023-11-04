#include <iostream>
#include <string> // std::getline
#include <vector>
#include <map>
#include <set>
#include <algorithm> // std::ranges::minmax_element

struct Point
{
	int x, y;

	auto operator<=>(const Point&) const = default;
};

struct Elf
{
	Point pos, next;
};

constexpr int rounds = 10;

constexpr Point offsets[]{
	Point{  0, -1 }, // north
	Point{  1, -1 }, // north-east
	Point{  1,  0 }, // east
	Point{  1,  1 }, // south-east
	Point{  0,  1 }, // south
	Point{ -1,  1 }, // south-west
	Point{ -1,  0 }, // west
	Point{ -1, -1 }  // north-west
};

constexpr unsigned north_mask =			0b00000001;
constexpr unsigned north_east_mask =	0b00000010;
constexpr unsigned east_mask =			0b00000100;
constexpr unsigned south_east_mask =	0b00001000;
constexpr unsigned south_mask =			0b00010000;
constexpr unsigned south_west_mask =	0b00100000;
constexpr unsigned west_mask =			0b01000000;
constexpr unsigned north_west_mask =	0b10000000;

constexpr unsigned move_north_mask = north_west_mask | north_mask | north_east_mask;
constexpr unsigned move_south_mask = south_west_mask | south_mask | south_east_mask;
constexpr unsigned move_west_mask = north_west_mask | west_mask | south_west_mask;
constexpr unsigned move_east_mask = north_east_mask | east_mask | south_east_mask;

constexpr struct { Point p; unsigned mask; } directions[]{
	{ Point{ 0, -1 }, move_north_mask },
	{ Point{ 0, 1 }, move_south_mask },
	{ Point{ -1, 0 }, move_west_mask },
	{ Point{ 1, 0 }, move_east_mask }
};

int main(int _, const char*[])
{
	std::vector<Elf> elves;

	Point p{};
	for (std::string line; std::getline(std::cin, line); )
	{
		p.x = 0;
		for (const char c : line)
		{
			if (c == '#')
				elves.emplace_back(p, Point{});

			p.x++;
		}
		p.y++;
	}

	for (int round = 0; round < rounds; round++)
	{
		std::set<Point> points;
		for (const auto& [pos, _] : elves)
			points.insert(pos);

		std::map<Point, int> next_points;

		for (auto& [pos, next] : elves)
		{
			unsigned neighbours{};
			for (unsigned m = 1; const auto& [ox, oy] : offsets)
			{
				if (points.contains(Point{ pos.x + ox, pos.y + oy }))
					neighbours |= m;

				m <<= 1;
			}

			next = pos;

			if (neighbours != 0u)
			{
				for (int i = 0; i < 4; i++)
				{
					const auto& [dir, mask] = directions[(i + round) % 4];
					if ((neighbours & mask) == 0)
					{
						next.x += dir.x;
						next.y += dir.y;
						next_points[next]++;
						break;
					}
				}
			}
		}

		for (auto& [pos, next] : elves)
		{
			if (pos != next)
			{
				if (auto it = next_points.find(next); it == next_points.end() || it->second < 2)
				{
					pos = next;
				}
			}
		}
	}

	const auto [left_it, right_it] = std::ranges::minmax_element(elves, [](auto e1, auto e2) { return e1.pos.x < e2.pos.x; });
	const auto [top_it, bottom_it] = std::ranges::minmax_element(elves, [](auto e1, auto e2) { return e1.pos.y < e2.pos.y; });

	const int min_x = left_it->pos.x;
	const int width = right_it->pos.x + 1 - min_x;
	const int min_y = top_it->pos.y;
	const int height = bottom_it->pos.y + 1 - min_y;

	std::cout << width * height - elves.size();
}