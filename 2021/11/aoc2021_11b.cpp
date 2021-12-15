#include <iostream>
#include <string>
#include <algorithm> // std::transform

constexpr int size = 10;
constexpr int L = size - 1;

struct Grid
{
	int energy[size][size];

	int inc(const int x, const int y)
	{
		if (++energy[y][x] == 10)
		{
			int flashes = 1;
			if (x > 0 && y > 0)	flashes += inc(x - 1, y - 1);
			if (x > 0) 			flashes += inc(x - 1, y);
			if (x > 0 && y < L)	flashes += inc(x - 1, y + 1);
			if (y < L)			flashes += inc(x,     y + 1);
			if (x < L && y < L) flashes += inc(x + 1, y + 1);
			if (x < L)			flashes += inc(x + 1, y);
			if (x < L && y > 0)	flashes += inc(x + 1, y - 1);
			if (y > 0)			flashes += inc(x,     y - 1);
			return flashes;
		}
		return 0;
	}
};

int main(int argc, const char* argv[])
{
	Grid grid = {};

	for (int y = 0; y < size; y++)
	{
		std::string row;
		std::cin >> row;
		std::transform(row.begin(), row.end(),
			std::begin(grid.energy[y]),
			[] (const char c) -> int { return c - '0'; });
	}

	for (int step = 1; ; step++)
	{
		Grid next = grid;

		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
				next.inc(x, y);

		int count = 0;
		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
				if (next.energy[y][x] > 9)
				{
					next.energy[y][x] = 0;
					count++;
				}

		if (count == size * size)
		{
			next.print();
			std::cout << step;
			break;
		}

		grid = next;
	}

	return 0;
}