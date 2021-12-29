#include <iostream>
#include <sstream>
#include <vector>

bool direction_to_delta(const char direction, int& dx, int& dy)
{
	dx = 0, dy = 0;
	switch (direction)
	{
	case 'L': dx = -1; break;
	case 'R': dx = 1; break;
	case 'U': dy = -1; break;
	case 'D': dy = 1; break;
	default: return false;
	};
	return true;
}

struct Line
{
	int x, y, dx, dy, length;
};

struct Point
{
	int x, y;
};

// Ax = b
bool solve(const int a11, const int a12, const int a21, const int a22,
		   const int b1, const int b2,
		   int& x1, int& x2)
{
	const int det = a11 * a22 - a12 * a21;

	if (det == 0)
		return false;

	x1 = (a22 * b1 - a12 * b2) / det;
	x2 = (a11 * b2 - a21 * b1) / det;

	return true;
}

bool intersects(const Line& a, const Line& b, Point& p)
{
	int u, v;
	if (solve(a.dx, -b.dx, a.dy, -b.dy, b.x - a.x, b.y - a.y, u, v) &&
		u >= 0 && u <= a.length && v >= 0 && v <= b.length)
	{
		p.x = a.x + u * a.dx;
		p.y = a.y + u * a.dy;
		return true;
	}
	return false;
}

using Path = std::vector<Line>;

Path read_path()
{
	Path path;

	std::string line;
	std::getline(std::cin, line);

	std::stringstream ss(line);

	int x = 0, y = 0;

	char direction;
	int length;
	while (ss >> direction, ss >> length)
	{
		Line line;
		line.x = x;
		line.y = y;
		line.length = length;
		direction_to_delta(direction, line.dx, line.dy);

		x += length * line.dx;
		y += length * line.dy;

		path.push_back(line);

		ss.ignore(1);
	}

	return path;
}

int main(int argc, const char* argv[])
{
	const Path path_a = read_path();
	const Path path_b = read_path();

	int min_distance = INT_MAX;

	for (const auto& a : path_a)
	{
		for (const auto& b : path_b)
		{
			Point p;
			if (intersects(a, b, p))
			{
				const int distance = std::abs(p.x) + std::abs(p.y);
				if (distance < min_distance)
					min_distance = distance;
			}
		}
	}

	std::cout << min_distance;

	return 0;
}