#include <iostream>

#include "../../util/Grid.hpp"

constexpr int Size = 3;

bool is_match(const auto& grid, const int x, const int y)
{
	return
		(grid[x + 1, y + 1] == 'A')
		&&
		(
			(grid[x, y] == 'M' && grid[x + 2, y + 2] == 'S')
			||
			(grid[x, y] == 'S' && grid[x + 2, y + 2] == 'M')
		)
		&&
		(
			(grid[x, y + 2] == 'M' && grid[x + 2, y] == 'S')
			||
			(grid[x, y + 2] == 'S' && grid[x + 2, y] == 'M')
		);
}

int main(int _, const char*[])
{
	util::Grid grid;
	std::cin >> grid;
	
	int count = 0;

	for (int x = 0; x <= grid.width() - Size; x++)
	{
		for (int y = 0; y <= grid.height() - Size; y++)
		{
			if (is_match(grid, x, y))
				count++;
		}
	}

	std::cout << count;
}