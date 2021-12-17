#include <iostream>
#include <string>
#include <set>
#include <algorithm> // std::transform
#include <iterator> // std::inserter

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

	std::getline(std::cin, line) && !line.empty();

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

	std::cout << folded_dots.size();

	return 0;
}