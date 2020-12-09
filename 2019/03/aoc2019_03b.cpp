#include <cstdio>
#include <vector>

void direction_to_delta(const char direction, int& dx, int& dy)
{
	switch (direction)
	{
	case 'L':
		dx = -1, dy = 0;
		break;
	case 'R':
		dx = 1, dy = 0;
		break;
	case 'U':
		dx = 0, dy = -1;
		break;
	case 'D':
		dx = 0, dy = 1;
		break;
	};
}

int abs(const int x)
{
	return x < 0 ? -x : x;
}

struct line_t
{
	int steps;
	int start_x, start_y;
	int dx, dy, length;
};

bool solve(const int (&A)[2][2], const int (&Y)[2], int (&X)[2])
{
	const int det_r = A[0][0] * A[1][1] - A[0][1] * A[1][0];

	if (det_r == 0)
		return false;

	X[0] = (A[1][1] * Y[0] - A[0][1] * Y[1]) / det_r;
	X[1] = (A[0][0] * Y[1] - A[1][0] * Y[0]) / det_r;

	return true;
}

bool intersect(const line_t& a, const line_t& b, int& u, int& v)
{
	// a.x + u * a.dx = b.x + v * b.x
	// a.y + u * a.dy = b.y + v * b.y

	// u * a.dx + v * (-b.dx) = (b.x - a.x)
	// u * a.dy + v * (-b.dy) = (b.y - a.y)

	// [ a.dx -b.dx ] [u] - [b.x - a.x]
	// [ a.dy -b.dy ] [v] - [b.y - a.y]

	const int A[2][2] = {
		{ a.dx, -b.dx },
		{ a.dy, -b.dy },
	};

	const int Y[2] = {
		b.start_x - a.start_x,
		b.start_y - a.start_y,
	};

	int X[2];
	if (!solve(A, Y, X))
		return false;

	u = X[0];
	v = X[1];

	return true;
}

int main(int argc, const char* argv[])
{
	std::vector<line_t> paths[2];

	for (auto& path : paths)
	{
		int x = 0, y = 0;
		int steps = 0;

		char direction;
		int length;
		while (scanf_s("%c%d", &direction, 1u, &length) == 2)
		{
			line_t line;
			line.start_x = x;
			line.start_y = y;
			line.length = length;
			line.steps = steps;
			direction_to_delta(direction, line.dx, line.dy);

			x += length * line.dx;
			y += length * line.dy;
			steps += length;

			path.push_back(line);

			if (getchar() == '\n')
				break;
		}
	}

	int min_steps = 100000;

	for (const line_t& a : paths[0])
	{
		for (const line_t& b : paths[1])
		{
			int u, v;
			if (intersect(a, b, u, v))
				if (u > 0 && u <= a.length && v > 0 && v <= b.length)
				{
					const int steps = a.steps + u + b.steps + v;
					if (steps < min_steps)
						min_steps = steps;
				}
		}
	}

	printf("min steps: %d\n", min_steps);

	return 0;
}