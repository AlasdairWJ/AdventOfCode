#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::count

int main(int _, const char*[])
{
	std::vector<std::string> grid;
	for (std::string line; std::getline(std::cin, line); )
		grid.push_back(line);

	const std::size_t size = grid.size();
 
	for (std::size_t y = 0; y < size; y++)
		for (std::size_t x = y + 1; x < size; x++)
			std::swap(grid[y][x], grid[x][y]);

	for (auto& row : grid)
	{
		std::size_t x = 0;

		while (x < size)
		{
			x = row.find_first_not_of('#', x);
			if (x == std::string::npos)
				break;

			std::size_t x2 = row.find('#', x);
			if (x2 == std::string::npos)
				x2 = size;

			const std::size_t rocks = std::count(row.data() + x, row.data() + x2, 'O');
			std::fill(row.data() + x, row.data() + x + rocks, 'O');
			std::fill(row.data() + x + rocks, row.data() + x2, '.');

			x = x2;
		}
	}

	int total = 0;

	for (auto& row : grid)
		for (std::size_t x = 0; x < size; x++)
			if (row[x] == 'O')
				total += size - x;

	std::cout << total;
}