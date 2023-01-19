#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <utility> // std::pair
#include <set> // std::set
#include <cmath> // std::abs

int main(int argc, const char* argv[])
{
	using point = std::pair<int, int>;

	point knots[10] = {};

	point& head = knots[0];
	auto& [head_x, head_y] = head;

	const point& tail = knots[9];
	const auto& [tail_x, tail_y] = tail;

	std::set<point> locations { tail };

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		char direction;
		int count;
		sscanf_s(buffer.c_str(), "%c %d", &direction, 1u, &count);

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
			}

			for (int i = 1; i < 10; i++)
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

	return 0;
}