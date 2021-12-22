#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <numeric> // std::gcd

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

struct Direction
{
	Direction(const int x, const int y) : x(x), y(y) {}
	double angle() const { return x == 0 && y < 0 ? -M_PI : std::atan2(-x, y); }
	bool operator<(const Direction& other) const { return angle() < other.angle(); }
	int x, y;
};

int main(int argc, const char* argv[])
{
	std::vector<std::string> grid;

	std::string line;
	while (std::getline(std::cin, line))
		grid.push_back(line);

	const int size_y = grid.size();
	const int size_x = grid[0].size();

	auto count_visible_asteroids_from = [&] (const int sx, const int sy) -> int
	{
		int count = 0;

		for (int ay = 0; ay < size_y; ++ay)
		{
			for (int ax = 0; ax < size_x; ++ax)
			{
				if (ax == sx && ay == sy)
					continue;

				if (grid[ay][ax] != '#')
					continue;

				int dx = ax - sx;
				int dy = ay - sy;
				if (dx == 0 || dy == 0)
				{
					dx = sgn(dx);
					dy = sgn(dy);
				}
				else
				{
					const int gcd = std::gcd(std::abs(dx), std::abs(dy));
					dx /= gcd;
					dy /= gcd;
				}

				bool is_visible = true;
				for (int x = sx + dx, y = sy + dy; x != ax || y != ay; x += dx, y += dy)
					if (grid[y][x] == '#')
						is_visible = false;

				count += is_visible;
			}
		}

		return count;
	};

	int best_c = 0, sx, sy;
	for (int y = 0; y < size_y; ++y)
	{
		for (int x = 0; x < size_x; ++x)
		{
			if (grid[y][x] == '.')
				continue;
			
			const int c = count_visible_asteroids_from(x, y);
			if (c > best_c)
			{
				best_c = c;
				sx = x, sy = y;
			}
		}
	}
	
	std::set<Direction> directions;
	
	for (int y = 0; y < size_y; ++y)
	{
		for (int x = 0; x < size_x; ++x)
		{
			int dx = x - sx;
			int dy = y - sy;
			if (dx == 0 || dy == 0)
			{
				if (std::abs(dx + dy) == 1)
					directions.emplace(dx, dy);
			}
			else
			{
				const int gcd = std::gcd(std::abs(dx), std::abs(dy));
				if (gcd == 1)
					directions.emplace(dx / gcd, dy / gcd);
			}
		}
	}

	int count = 0;
	while (true)
	{
		for (const auto& direction : directions)
		{
			int x = sx + direction.x;
			int y = sy + direction.y;

			while (x >= 0 && y >= 0 && x < size_x && y < size_y)
			{
				if (grid[y][x] == '#')
				{
					std::cout << "destroyed #" << count << ": " << x << ", " << y << std::endl;
					grid[y][x] = '.';
					if (++count == 200)
					{
						std::cout << x * 100 + y;
						return 0;
					}
					break;
				}

				x += direction.x;
				y += direction.y;
			}
		}
	}
}
	/*
	directions.emplace( 1,  1);
	directions.emplace( 1,  0);
	directions.emplace( 1, -1);
	directions.emplace( 0, -1);
	directions.emplace(-1, -1);
	directions.emplace(-1,  0);
	directions.emplace(-1,  1);
	directions.emplace( 0,  1);

	for (const auto& d : directions)
		printf("%d, %d - %.3lf\n", d.x, d.y, d.angle());

	return 0;
*/