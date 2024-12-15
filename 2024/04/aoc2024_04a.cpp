#include <iostream>

#include "../../util/Grid.hpp"

constexpr char XMAS[]{ 'X', 'M', 'A', 'S' };
constexpr int Size = std::size(XMAS);

constexpr int directions[][2]{
	{  1,  0 },
	{  1, -1 },
	{  0, -1 },
	{ -1, -1 },
	{ -1,  0 },
	{ -1,  1 },
	{  0,  1 },
	{  1,  1 }
};

bool is_match(const auto& grid, int x, int y, const int dx, const int dy)
{
	for (int n = 0; n < Size; n++, x += dx, y += dy)
	{
		if (grid[x, y] != XMAS[n])
			return false;
	}

	return true;
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;

	int count = 0;

	for (int x = 0; x < grid.width(); x++)
	{
		for (int y = 0; y < grid.height(); y++)
		{
			for (const auto [dx, dy] : directions)
			{
				const bool in_bounds = grid.in_bounds(x + dx * (Size - 1), y + dy * (Size - 1));
				if (in_bounds && is_match(grid, x, y, dx, dy))
					count++;
			}
		}
	}

	std::cout << count;
}