#include <iostream>
#include <set>
#include <cmath> // std::abs

constexpr int N = 10;

struct point
{
	int x, y;

	auto operator<=>(const point&) const = default;
};

int main(int _, const char*[])
{
	point knots[N]{};

	auto& [head_x, head_y] = knots[0];

	const point& tail = knots[N - 1];
	const auto& [tail_x, tail_y] = tail;

	std::set<point> locations { tail };

	char direction;
	int count;
	while (std::cin >> direction, std::cin.ignore(1), std::cin >> count)
	{
		for  (int i = 0; i < count; i++)
		{
			switch (direction)
			{
			case 'L':
				head_x--;
				break;
			case 'R':
				head_x++;
				break;
			case 'U':
				head_y--;
				break;
			case 'D':
				head_y++;
				break;
			default:
				break;
			}

			for (int i = 1; i < N; i++)
			{
				auto& [knot_x, knot_y] = knots[i];
				const auto& [prev_knot_x, prev_knot_y] = knots[i - 1];

				const int dx = knot_x - prev_knot_x;
				const int dy = knot_y - prev_knot_y;

				if (dx < -1 || (dx == -1 && std::abs(dy) > 1))
					knot_x++;

				if (dx > 1 || (dx == 1 && std::abs(dy) > 1))
					knot_x--;

				if (dy < -1 || (dy == -1 && std::abs(dx) > 1))
					knot_y++;

				if (dy > 1 || (dy == 1 && std::abs(dx) > 1))
					knot_y--;
			}

			locations.insert(tail);
		}
	}

	std::cout << locations.size();
}