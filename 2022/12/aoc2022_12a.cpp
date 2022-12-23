#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>

struct point { int x, y; };

bool operator<(const point& a, const point& b)
{
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

int main(int argc, const char* argv[])
{
	std::vector<std::string> rows;

	point start, target;

	std::string buffer;
	std::getline(std::cin, buffer);
	
	const int width = buffer.size();

	do
	{
		for (int i = 0; i < width; i++)
		{
			char& c = buffer[i];
			if (c == 'S')
			{
				c = 'a';
				start.x = i;
				start.y = rows.size();
			}
			else if (c == 'E')
			{
				c = 'z';
				target.x = i;
				target.y = rows.size();
			}
		}

		rows.push_back(buffer);
	}
	while (std::getline(std::cin, buffer));

	const int height = rows.size();

	const auto _visited = std::make_unique<bool[]>(width * height);
	
	const auto visited = [&](const point& p) -> bool&
	{
		return _visited[p.y * width + p.x];
	};
	
	const auto at = [&](const point& p) -> char
	{
		return rows[p.y][p.x];
	};

	visited(start) = true;

	int steps = 0;

	for (std::set<point> current { start };
		!current.empty() && current.find(target) == current.end();
		steps++)
	{
		std::set<point> next;

		for (const auto& p : current)
		{
			const char c = at(p);

			if (p.x > 0)
			{
				const point left { p.x - 1, p.y };
				if (bool& v = visited(left); !v && at(left) <= c + 1)
					next.insert(left), v = true;
			}

			if (p.x < width - 1)
			{
				const point right { p.x + 1, p.y };
				if (bool& v = visited(right); !v && at(right) <= c + 1)
					next.insert(right), v = true;
			}

			if (p.y > 0)
			{
				const point above { p.x, p.y - 1 };
				if (bool& v = visited(above); !v && at(above) <= c + 1)
					next.insert(above), v = true;
			}

			if (p.y < height - 1)
			{
				const point below { p.x, p.y + 1 };
				if (bool& v = visited(below); !v && at(below) <= c + 1)
					next.insert(below), v = true;
			}
		}

		current.swap(next);
	}

	std::cout << steps;

	return 0;
}