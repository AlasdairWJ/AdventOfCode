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
	point head = {}, tail = {};
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

			const int dx = tail.x - head.x;
			const int dy = tail.y - head.y;

			if (dx < -1 || (dx == -1 && abs(dy) > 1))
				tail.x++;
			if (dx > 1 || (dx == 1 && abs(dy) > 1))
				tail.x--;

			if (dy < -1 || (dy == -1 && abs(dx) > 1))
				tail.y++;
			if (dy > 1 || (dy == 1 && abs(dx) > 1))
				tail.y--;

			locations.emplace(tail);

			//printf("(%d, %d), (%d, %d)\n", head.x, head.y, tail.x, tail.y);
		}
	}

	std::cout << locations.size();	

	return 0;
}