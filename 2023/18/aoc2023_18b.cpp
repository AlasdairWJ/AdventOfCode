#include <iostream>
#include <string> // std::getline
#include <vector>
#include <ranges> // std::views::pairwise
#include <map>
#include <set>

#include "../../util/separate.hpp" // util::separate
#include "../../util/charconv.hpp" // util::from_hex_chars
#include "../../util/numeric.hpp" // util::sign

struct Point
{
	int x, y;
};

template <typename T>
bool is_between(const T value, const T& a, const T& b)
{
	return (a < b)
		? (a <= value && value <= b)
		: (b <= value && value <= a);
}

int main(int _, const char*[])
{
	Point p{};
	std::vector<Point> polygon{ p };

	Point minP, maxP;

	long long total = 0;

	std::set<int> ys;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto hex = util::separate<3>(line)[2];

		int dist;
		util::from_hex_chars(hex.substr(2, 5), dist); // (#70c710) -> 70c71

		switch (hex[7])
		{
		case '0': p.x += dist; break;
		case '1': p.y += dist; break;
		case '2': p.x -= dist; break;
		case '3': p.y -= dist; break;
		default: break;
		}

		polygon.push_back(p);
		ys.insert(p.y);
		ys.insert(p.y + 1);

		minP.x = std::min(p.x, minP.x);
		minP.y = std::min(p.y, minP.y);
		maxP.x = std::max(p.x, maxP.x);
		maxP.y = std::max(p.y, maxP.y);
	}

	for (const auto [y, next_y] : ys | std::views::pairwise)
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
		int count = 0;

		for (const auto [x, dir] : walls)
		{
			if (c == 0)
			{
				last_zero_x = x;
			}

			c += dir;

			if (c == 0)
			{
				count += (x - last_zero_x + 1);
			}
		}

		total += static_cast<long long>(next_y - y) * count;
	}

	std::cout << total;
}