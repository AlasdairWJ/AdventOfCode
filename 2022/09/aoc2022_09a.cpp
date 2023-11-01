#include <iostream>
#include <set>
#include <cmath> // std::abs

struct point
{
	int x, y;

	auto operator<=>(const point&) const = default;
};

int main(int _, const char*[])
{
	point head = {};
	auto& [head_x, head_y] = head;

	point tail = {};
	auto& [tail_x, tail_y] = tail;

	std::set<point> locations{ tail };

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

			const int dx = tail_x - head_x;
			const int dy = tail_y - head_y;

			if (dx < -1 || (dx == -1 && std::abs(dy) > 1))
				tail_x++;

			if (dx > 1 || (dx == 1 && std::abs(dy) > 1))
				tail_x--;

			if (dy < -1 || (dy == -1 && std::abs(dx) > 1))
				tail_y++;

			if (dy > 1 || (dy == 1 && std::abs(dx) > 1))
				tail_y--;

			locations.insert(tail);
		}
	}

	std::cout << locations.size();
}