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

bool do_walk(const auto& lines, const Point start_p, std::set<Point>* pLocations = nullptr)
{
	std::set<Point> corners;

	const int height = static_cast<int>(lines.size());
	const int width = static_cast<int>(lines.front().size());

	Point p = start_p, delta{ 0, -1 };

	for (;;)
	{
		Point q = p + delta;

		if (q.x < 0 || q.y < 0 || q.x >= width || q.y >= height)
			return false;

		if (lines[q.y][q.x] == '#')
		{
			const auto [_, is_new] = corners.emplace(p);

			if (!is_new)
				return true;

			delta.turn_right();
			q = p + delta;

			if (lines[q.y][q.x] == '#')
			{
				delta.turn_right();
				q = p + delta;
			}
		}

		p = q;

		if (pLocations != nullptr)
		{
			pLocations->insert(p);
		}
	}
}

int main(int _, const char*[])
{
	int start_x = -1;
	std::vector<std::string> lines;

	int start_y = 0;
	for (std::string line; std::getline(std::cin, line); )
	{
		if (start_x < 0)
		{
			if (const auto ix = line.find('^'); ix != std::string::npos)
				start_x = static_cast<int>(ix);
			else
				start_y++;
		}

		lines.push_back(line);
	}

	const int width = static_cast<int>(lines.front().size());
	const int height = static_cast<int>(lines.size());

	const Point start_p{ start_x, start_y };

	std::set<Point> locations;
	do_walk(lines, start_p, &locations);

	int count = 0;

	for (const auto [x, y] : locations)
	{
		if (char& c = lines[y][x]; c == '.')
		{
			c = '#';

			if (const bool looped = do_walk(lines, start_p); looped)
				count++;

			c = '.';
		}
	}

	std::cout << count;
}