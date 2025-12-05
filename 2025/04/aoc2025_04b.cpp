#include <iostream>
#include <string>
#include <vector>

int main()
{
	constexpr char Roll = '@';
	constexpr char Space = '.';

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

	std::vector<std::vector<int>> ngrid;

	for (int y = 0; y < rows; y++)
	{
		ngrid.emplace_back(cols);

		for (int x = 0; x < cols; x++)
			ngrid[y][x] = neighbours(x, y);
	}

	auto remove_roll = [&](const int x, const int y)
	{
		grid[y][x] = Space;

		if (y > 0)
		{
			if (x > 0)
				ngrid[y - 1][x - 1]--;

			ngrid[y - 1][x]--;

			if (x < cols - 1)
				ngrid[y - 1][x + 1]--;
		}

		if (x > 0)
			ngrid[y][x - 1]--;

		if (x < cols - 1)
			ngrid[y][x + 1]--;

		if (y < rows - 1)
		{
			if (x > 0)
				ngrid[y + 1][x - 1]--;

			ngrid[y + 1][x]--;

			if (x < cols - 1)
				ngrid[y + 1][x + 1]--;
		}
	};

	int total = 0;
	
	bool any_removed;

	do
	{
		any_removed = false;

		for (int y = 0; y < rows; y++)
		for (int x = 0; x < cols; x++)
		{
			if (grid[y][x] == Roll && ngrid[y][x] < 4)
			{
				remove_roll(x, y);
				total++;
				any_removed = true;
			}
		}
	}
	while (any_removed);

	std::cout << total;
}