#include <iostream>
#include <string> // std::getline
#include <vector>
#include <ranges> // std::views::pairwise
#include <map>

#include "../../util/separate.hpp" // util::separate
#include "../../util/charconv.hpp" // util::from_chars
#include "../../util/numeric.hpp" // util::sign

struct Point
{
	int x, y;
};

template <typename T>
bool is_between(const T value, const T& a, const T& b)
{
	if (a < b)
	{
		return a <= value && value <= b;
	}
	else
	{
		return b <= value && value <= a;
	}
}

int main(int _, const char*[])
{
	Point p{};
	std::vector<Point> polygon{ p };

	Point minP, maxP;

	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto [dir, dist_str, _] = util::separate<3>(line);

		int dist;
		util::from_chars(dist_str, dist);

		switch (dir[0])
		{
		case 'U': p.y -= dist; break;
		case 'R': p.x += dist; break;
		case 'D': p.y += dist; break;
		case 'L': p.x -= dist; break;
		default: break;
		}

		polygon.push_back(p);

		minP.x = std::min(p.x, minP.x);
		minP.y = std::min(p.y, minP.y);
		maxP.x = std::max(p.x, maxP.x);
		maxP.y = std::max(p.y, maxP.y);
	}

	for (int y = minP.y; y <= maxP.y; y++)
	{
		std::map<int, int> walls;

		for (const auto& [a, b] : polygon | std::views::pairwise)
		{
			if (a.x == b.x)
			{
				const int sign = util::sign(b.y - a.y);
				if (is_between(y, a.y, b.y))
				{
					const int multiplier = (y != a.y && y != b.y) ? 2 : 1;
					walls.emplace(a.x, multiplier * sign);
				}
			}
		}

		int last_zero_x;
		int c = 0;

		for (const auto [x, dir] : walls)
		{
			if (c == 0)
			{
				last_zero_x = x;
			}

			c += dir;

			if (c == 0)
			{
				total += (x - last_zero_x + 1);
			}
		}
	}

	std::cout << total;
}