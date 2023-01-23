#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <utility> // std::pair
#include <set> // std::set
#include <cmath> // std::abs

int main(int argc, const char* argv[])
{
	using point = std::pair<int, int>;

	point head = {};
	auto& [head_x, head_y] = head;

	point tail = {};
	auto& [tail_x, tail_y] = tail;

	std::set<point> locations { tail };

	std::string line;
	while (std::getline(std::cin, line))
	{
		char direction;
		int count;
		sscanf_s(line.c_str(), "%c %d", &direction, 1u, &count);

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

	return 0;
}