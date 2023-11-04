#include <iostream>
#include <string> // std::getline
#include <vector>
#include <utility>
#include <set>

struct Point
{
	int x, y;

	auto operator<=>(const Point&) const = default;
};

int main(int _, const char*[])
{
	std::vector<std::string> rows;

	Point start, target;

	for (std::string line; std::getline(std::cin, line); )
		rows.push_back(line);

	const int width = static_cast<int>(rows.front().size());
	const int height = static_cast<int>(rows.size());

	for (Point p{}; auto& row : rows)
	{
		for (p.x = 0; char& c : row)
		{
			switch (c)
			{
			case 'S':
				c = 'a';
				start = p;
				break;
			case 'E':
				c = 'z';
				target = p;
				break;
			default:
				break;
			}

			p.x++;
		}

		p.y++;
	}

	std::vector<int8_t> data(width * height);

	auto visited = [&](const Point& p) -> int8_t&
	{
		return data.at(p.y * width + p.x);
	};

	auto at = [&](const Point& p) -> char
	{
		return rows[p.y][p.x];
	};

	std::set<Point> current;

	for (Point p{}; p.y < height; p.y++)
		for (p.x = 0; p.x < width; p.x++)
			if (at(p) == 'a')
				current.insert(p), visited(p) = true;

	int steps = 0;

	for (; !current.contains(target); steps++)
	{
		std::set<Point> next;

		for (const auto& p : current)
		{
			const char c = at(p);

			if (p.x > 0)
			{
				const Point left{ p.x - 1, p.y };
				if (auto& v = visited(left); !v && at(left) <= c + 1)
					next.insert(left), v = true;
			}

			if (p.x < width - 1)
			{
				const Point right{ p.x + 1, p.y };
				if (auto& v = visited(right);  !v && at(right) <= c + 1)
					next.insert(right), v = true;
			}

			if (p.y > 0)
			{
				const Point above{ p.x, p.y - 1 };
				if (auto& v = visited(above); !v && at(above) <= c + 1)
					next.insert(above), v = true;
			}

			if (p.y < height - 1)
			{
				const Point below{ p.x, p.y + 1 };
				if (auto& v = visited(below); !v && at(below) <= c + 1)
					next.insert(below), v = true;
			}
		}

		current.swap(next);
	}

	std::cout << steps;
}