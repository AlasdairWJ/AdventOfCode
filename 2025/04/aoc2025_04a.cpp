#include <iostream>
#include <string>
#include <vector>

int main()
{
	constexpr char Roll = '@';

	std::vector<std::string> grid;

	for (std::string line; std::getline(std::cin, line); )
		grid.push_back(line);

	const int rows = grid.size();
	const int cols = grid[0].size();

	auto neighbours = [&](const int x, const int y) -> int
	{
		int count = 0;

		if (y > 0)
		{
			if (x > 0)
				count += (grid[y - 1][x - 1] == Roll);

			count += (grid[y - 1][x] == Roll);

			if (x < cols - 1)
				count += (grid[y - 1][x + 1] == Roll);
		}

		if (x > 0)
			count += (grid[y][x - 1] == Roll);

		if (x < cols - 1)
			count += (grid[y][x + 1] == Roll);

		if (y < rows - 1)
		{
			if (x > 0)
				count += (grid[y + 1][x - 1] == Roll);

			count += (grid[y + 1][x] == Roll);

			if (x < cols - 1)
				count += (grid[y + 1][x + 1] == Roll);
		}

		return count;
	};

	int total = 0;

	for (int y = 0; y < rows; y++)
	for (int x = 0; x < cols; x++)
	{
		if (grid[y][x] == Roll && neighbours(x, y) < 4)
			total++;
	}

	std::cout << total;
}