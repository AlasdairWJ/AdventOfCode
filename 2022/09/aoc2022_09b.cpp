#include <iostream>
#include <string>
#include <set>
#include <cmath>

struct point { int x, y; };

bool operator<(const point& a, const point& b)
{
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

int main(int argc, const char* argv[])
{
	point knots[10] = {};
	point &head = knots[0], &tail = knots[9];

	std::set<point> locations { tail };

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		const char direction = buffer[0];
		const int count = std::stoi(buffer.substr(2));

		for  (int i = 0; i < count; i++)
		{
			switch (direction)
			{
			case 'L':
				head.x--;
				break;
			case 'R':
				head.x++;
				break;
			case 'U':
				head.y--;
				break;
			case 'D':
				head.y++;
				break;
			}

			for (int i = 1; i < 10; i++)
			{
				point &knot = knots[i];
				const int dx = knot.x - knots[i - 1].x;
				const int dy = knot.y - knots[i - 1].y;

				if (dx < -1 || (dx == -1 && abs(dy) > 1))
					knot.x++;
				if (dx > 1 || (dx == 1 && abs(dy) > 1))
					knot.x--;

				if (dy < -1 || (dy == -1 && abs(dx) > 1))
					knot.y++;
				if (dy > 1 || (dy == 1 && abs(dx) > 1))
					knot.y--;
			}

			locations.emplace(tail);
		}
	}

	std::cout << locations.size();	

	return 0;
}