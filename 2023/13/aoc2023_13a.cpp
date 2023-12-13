#include <iostream>
#include <string> // std::getline
#include <vector>
#include <algorithm> // std::min, std::ranges::equal, std::all_of
#include <string_view>
#include <ranges> // std::views::reverse

bool is_mirrored_at(const std::string& line, const std::size_t index)
{
	const std::size_t n = std::min(index, line.size() - index);

	if (n == 0)
		return false;

	const auto left = std::string_view{ line }.substr(index - n, n);
	const auto right = std::string_view{ line }.substr(index, n);

	return std::ranges::equal(left, right | std::views::reverse);
}

std::size_t find_reflection_index(const std::vector<std::string>& grid)
{
	const auto& first = grid.front();

	for (std::size_t index = 1; index < first.size(); index++)
	{
		if (std::ranges::all_of(grid, [&](const auto& line) { return is_mirrored_at(line, index); }))
		{
			return index;
		}
	}

	return 0; // not found
}

int main(int _, const char*[])
{
	int total = 0;

	for (int i = 0; std::cin; i++)
	{
		std::vector<std::string> grid;

		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
			grid.push_back(line);

		std::vector<std::string> grid_flipped{ grid.front().size(), std::string(grid.size(), '\0') };

		for (std::size_t x = 0; x < grid_flipped.size(); x++)
			for (std::size_t y = 0; y < grid.size(); y++)
				grid_flipped[x][y] = grid[y][x];

		total += find_reflection_index(grid) + 100 * find_reflection_index(grid_flipped);
	}

	std::cout << total;
}