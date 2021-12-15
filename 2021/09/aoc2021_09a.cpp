#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, const char* argv[])
{
	std::vector<std::vector<int>> grid;

	int y = 0;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::vector<int> row(line.size());
		std::transform(line.begin(), line.end(), row.begin(),
			[](const char l) -> int { return l - '0'; });
		grid.push_back(row);
	}

	int total = 0;

	const int h = grid.size();
	for (int y = 0; y < h; y++)
	{
		const int w = grid[y].size();
		for (int x = 0; x < w; x++)
		{
			const int v = grid[y][x];

			if ((x == 0 || grid[y][x-1] > v) &&
				(y == 0 || grid[y-1][x] > v) && 
				(x == w-1 || grid[y][x+1] > v) &&
				(y == h-1 || grid[y+1][x] > v))
			{
				total += 1 + v;
			}
		}
	}

	std::cout << total;

	return 0;
}