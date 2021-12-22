#include <iostream>
#include <string>
#include <vector>
#include <numeric> // std::gcd

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

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

	int best_c = 0;
	for (int y = 0; y < size_y; ++y)
	{
		for (int x = 0; x < size_x; ++x)
		{
			if (grid[y][x] == '.')
			{
				std::cout << ' ';
				continue;
			}
			
			const int c = count_visible_asteroids_from(x, y);
			if (c > best_c)
				best_c = c;
		}
	}
	
	std::cout << best_c;
	
	return 0;
}