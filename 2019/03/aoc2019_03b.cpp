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

bool intersects(const Line& a, const Line& b, int& u, int& v)
{
	return solve(a.dx, -b.dx, a.dy, -b.dy, b.x - a.x, b.y - a.y, u, v) &&
		   u >= 0 && u <= a.length && v >= 0 && v <= b.length;
}

using Path = std::vector<std::pair<Line, int>>;

Path read_path()
{
	Path path;

	std::string line;
	std::getline(std::cin, line);

	std::stringstream ss(line);

	int x = 0, y = 0;
	int steps = 0;

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

		path.emplace_back(line, steps);
		steps += length;

		ss.ignore(1);
	}

	return path;
}

int main(int argc, const char* argv[])
{
	const auto path_a = read_path();
	const auto path_b = read_path();

	int min_steps = INT_MAX;

	for (const auto& [a, a_steps] : path_a)
	{
		for (const auto& [b, b_steps] : path_b)
		{
			int u, v;
			if (intersects(a, b, u, v))
			{
				const int steps = a_steps + u + b_steps + v;
				if (steps < min_steps)
					min_steps = steps;
			}
		}
	}

	std::cout << min_steps;

	return 0;
}