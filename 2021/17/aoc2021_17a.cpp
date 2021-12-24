#include <iostream>
#include <string>
#include <cmath>

int tri(const int n) { return n * (n + 1) / 2; }

double n_from_tri(const int tn)
{
	return (std::sqrt(8*tn + 1) - 1.0) / 2.0;
}

int main(int argc, const char* argv[])
{
	std::string line;
	std::getline(std::cin, line);

	int x1, x2, y1, y2;
	sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);

	const auto test = [&](int dx, int dy) -> bool
	{
		int x = 0, y = 0;

		while (x <= x2 && y >= y2)
		{
			x += dx, y += dy;

			if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
			{
				return true;
			}

			if (dx > 0) dx--;
			dy--;
		}

		return false;
	};

	const int min_dx = static_cast<int>(std::ceil(n_from_tri(x1)));
	const int max_dx = x2;

	const int min_dy = y1;
	const int max_dy = -y1;

	int best_dy = 0, best_dx = 0;
	for (int dx = min_dx; dx <= max_dx; dx++)
	{
		for (int dy = min_dy; dy <= max_dy; dy++)
		{
			if (test(dx, dy) && dy > best_dy)
				best_dx = dx, best_dy = dy;
		}
	}

	std::cout << tri(best_dy);

	return 0;
}