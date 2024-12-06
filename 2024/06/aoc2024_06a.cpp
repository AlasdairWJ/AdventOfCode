#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Point
{
	int x, y;

	void turn_right()
	{
		std::tie(x, y) = std::make_pair(-y, x);
	}

	auto operator<=>(const Point& other) const = default;
};

Point operator+(const Point lhs, const Point rhs)
{
	return Point{ lhs.x + rhs.x, lhs.y + rhs.y };
}

int main(int _, const char*[])
{
	int start_x = -1;
	std::vector<std::string> lines;

	int start_y = 0;
	for (std::string line; std::getline(std::cin, line); )
	{
		lines.push_back(line);

		if (start_x < 0)
		{
			if (const auto ix = line.find('^'); ix != std::string::npos)
				start_x = static_cast<int>(ix);
			else
				start_y++;

		}
	}

	const int height = static_cast<int>(lines.size());
	const int width = static_cast<int>(lines.front().size());

	std::set<Point> history;
	Point p{ start_x, start_y}, delta{ 0, -1 };

	for (;;)
	{
		history.insert(p);

		Point q = p + delta;

		if (q.x < 0 || q.y < 0 || q.x >= width || q.y >= height)
			break;

		if (lines[q.y][q.x] == '#')
		{
			delta.turn_right();
			q = p + delta;
		}

		p = q;
	}

	std::cout << history.size();
}