#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm> // std::transform
#include <iterator> // std::inserter
#include <utility> // std::move

struct Point
{
	int x, y;

	Point() = default;
	Point(const int x, const int y) : x(x), y(y) {};
	bool operator<(const Point& other) const { return x < other.x || (x == other.x && y < other.y); }
};

int main(int argc, const char* argv[])
{
	std::set<Point> dots;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		Point p;
		sscanf_s(line.c_str(), "%d,%d", &p.x, &p.y);
		dots.insert(p);
	}

	while (std::getline(std::cin, line) && !line.empty())
	{
		std::set<Point> folded_dots;

		char axis;
		int value;
		sscanf_s(line.c_str(), "fold along %c=%d", &axis, 1u, &value);

		std::transform(
			dots.begin(), dots.end(),
			std::inserter(folded_dots, folded_dots.begin()),
			[&](Point p) {
				if (axis == 'x' && p.x > value)
					p.x = 2*value - p.x;
				else if (axis == 'y' && p.y > value)
					p.y = 2*value - p.y;
				return p;
			});

		dots = std::move(folded_dots);
	}

	Point lower = *dots.begin(), upper = *dots.begin(); 
	for (const auto& p : dots)
	{
		if (p.x < lower.x) lower.x = p.x;
		if (p.y < lower.y) lower.y = p.y;
		if (p.x > upper.x) upper.x = p.x;
		if (p.y > upper.y) upper.y = p.y;
	}

	const Point range(upper.x - lower.x + 1, upper.y - lower.y + 1);
	std::vector<std::string> display_buffer(range.y, std::string(range.x, ' '));

	for (const auto& p : dots)
		display_buffer[p.y - lower.y][p.x - lower.x] = '#';
	
	for (const auto& line : display_buffer)
		std::cout << line << std::endl;

	return 0;
}