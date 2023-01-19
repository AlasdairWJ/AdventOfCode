#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <array> // std::array
#include <set> // std::set
#include <cmath> // std::abs

int main(int argc, const char* argv[])
{
	using point = std::array<int, 2>;

	point knots[10] = {};
	point &head = knots[0], &tail = knots[9];

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

			for (int i = 1; i < 10; i++)
			{
				point& knot = knots[i];
				const int dx = knot[0] - knots[i - 1][0];
				const int dy = knot[1] - knots[i - 1][1];

				if (dx < -1 || (dx == -1 && std::abs(dy) > 1))
					knot[0]++;
				if (dx > 1 || (dx == 1 && std::abs(dy) > 1))
					knot[0]--;

				if (dy < -1 || (dy == -1 && std::abs(dx) > 1))
					knot[1]++;
				if (dy > 1 || (dy == 1 && std::abs(dx) > 1))
					knot[1]--;
			}

			locations.insert(tail);
		}
	}

	std::cout << locations.size();

	return 0;
}