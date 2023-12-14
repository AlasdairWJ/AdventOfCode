#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::count
#include <map>

constexpr std::size_t Cycle = 1'000'000'000;

auto& rotate(auto& grid)
{
	const auto size = std::size(grid);

	for (std::size_t x = 0; x < size / 2; x++)
	{
		for (std::size_t y = 0; y < size / 2; y++)
		{
			const auto temp = grid[y][x];
			grid[y][x] = grid[x][size - y - 1];
			grid[x][size - y - 1] = grid[size - y - 1][size - x - 1];
			grid[size - y - 1][size - x - 1] = grid[size - x - 1][y];
			grid[size - x - 1][y] = temp;
		}
	}

	return grid;
}

int main(int _, const char*[])
{
	std::vector<std::string> grid;
	for (std::string line; std::getline(std::cin, line); )
		grid.push_back(line);

	const std::size_t size = grid.size();

	for (std::size_t y = 0; y < size; y++)
		for (std::size_t x = y + 1; x < size; x++)
			std::swap(grid[y][x], grid[x][y]);

	std::map<std::string, std::size_t> history;
	std::vector<int> scores; // per cycle;

	for (std::size_t cycle = 0; ; cycle++)
	{
		{
			int score = 0;

			for (auto& row : grid)
				for (std::size_t x = 0; x < size; x++)
					if (row[x] == 'O')
						score += size - x;

			scores.push_back(score);
		}

		{
			std::string state;
			for (const auto& row : grid)
				state.append(row.begin(), row.end());

			const auto [it, is_new] = history.emplace(state, cycle);

			if (!is_new)
			{
				const std::size_t desired_cycle = it->second + (Cycle - it->second) % (cycle - it->second);
				std::cout << scores[desired_cycle];
				break;
			}
		}

		for (int turn = 0; turn < 4; turn++)
		{
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

			rotate(grid);
		}
	}
}