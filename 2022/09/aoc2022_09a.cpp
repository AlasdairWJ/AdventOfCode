#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <array> // std::array
#include <set> // std::set
#include <cmath> // std::abs

int main(int argc, const char* argv[])
{
	using point = std::array<int, 2>;

	point head = {}, tail = {};
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
				head[0]--;
				break;
			case 'R':
				head[0]++;
				break;
			case 'U':
				head[1]--;
				break;
			case 'D':
				head[1]++;
				break;
			}

			const int dx = tail[0] - head[0];
			const int dy = tail[1] - head[1];

			if (dx < -1 || (dx == -1 && std::abs(dy) > 1))
				tail[0]++;
			if (dx > 1 || (dx == 1 && std::abs(dy) > 1))
				tail[0]--;

			if (dy < -1 || (dy == -1 && std::abs(dx) > 1))
				tail[1]++;
			if (dy > 1 || (dy == 1 && std::abs(dx) > 1))
				tail[1]--;

			locations.insert(tail);
		}
	}

	std::cout << locations.size();

	return 0;
}