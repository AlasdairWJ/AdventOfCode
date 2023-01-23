#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> // std::vector
#include <utility> // std::pair
#include <set> // std::set

int main(int argc, const char* argv[])
{
	std::vector<std::string> rows;

	using point = std::pair<int, int>;
	point start, target;

	std::string line;
	std::getline(std::cin, line);

	const int width = line.size();

	do
	{
		for (int i = 0; i < width; i++)
		{
			if (char& c = line[i]; c == 'S')
			{
				c = 'a';
				start = point{ i, static_cast<int>(rows.size()) };
			}
			else if (c == 'E')
			{
				c = 'z';
				target = point{ i, static_cast<int>(rows.size()) };
			}
		}

		rows.push_back(line);
	}
	while (std::getline(std::cin, line));

	const int height = rows.size();

	const auto visited = [&](const point& p) -> int8_t&
	{
		static std::vector<int8_t> data(width * height);
		return data.at(p.second * width + p.first);
	};

	const auto at = [&](const point& p) -> char
	{
		return rows[p.second][p.first];
	};

	visited(start) = true;

	int steps = 0;

	for (std::set<point> current{ start };
		 !current.empty() && current.find(target) == current.end();
		 steps++)
	{
		std::set<point> next;

		for (const auto& p : current)
		{
			const auto& [x, y] = p;
			const char c = at(p);

			if (x > 0)
			{
				const point left{ x - 1, y };
				if (int& v = visited(left); !v && at(left) <= c + 1)
					next.insert(left), v = true;
			}

			if (x < width - 1)
			{
				const point right{ x + 1, y };
				if (int& v = visited(right); !v && at(right) <= c + 1)
					next.insert(right), v = true;
			}

			if (y > 0)
			{
				const point above{ x, y - 1 };
				if (int& v = visited(above); !v && at(above) <= c + 1)
					next.insert(above), v = true;
			}

			if (y < height - 1)
			{
				const point below{ x, y + 1 };
				if (int& v = visited(below); !v && at(below) <= c + 1)
					next.insert(below), v = true;
			}
		}

		current.swap(next);
	}

	std::cout << steps;

	return 0;
}