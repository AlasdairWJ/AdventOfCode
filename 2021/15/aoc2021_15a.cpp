#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::transform

int main(int argc, const char* argv[])
{
	std::vector<std::vector<int>> risk_grid;

	std::string line;
	while (std::getline(std::cin, line) && !line.empty())
	{
		std::vector<int> row(line.size());
		std::transform(line.begin(), line.end(), row.begin(), [](char x) { return x - '0'; });

		risk_grid.push_back(row);
	}

	const int max_y = risk_grid.size() - 1;
	const int max_x = risk_grid[0].size() - 1;

	for (int i = 1; i <= max_y + max_x; i++)
	{
		for (int x = std::max(0, i - max_y), y = std::min(i, max_y); y >= 0 && x <= max_x; x++, y--)
		{
			int& risk = risk_grid[y][x];

			if (y == 0)
			{
				risk += risk_grid[y][x - 1];
			}
			else if (x == 0)
			{
				risk += risk_grid[y - 1][x];
			}
			else
			{
				risk += std::min(risk_grid[y - 1][x], risk_grid[y][x - 1]);
			}
		}
	}

	std::cout << risk_grid[max_y][max_x] - risk_grid[0][0];

	return 0;
}