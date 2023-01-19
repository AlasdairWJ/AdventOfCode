#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> // std::vector
#include <numeric> // std::accumulate

int main(int argc, const char* argv[])
{
	std::vector<std::string> heights;

	std::string line;
	while (std::getline(std::cin, line))
		heights.push_back(line);

	const int row_count = heights.size();
	const int col_count = heights.front().size();
	const int tree_count = row_count * col_count;

	std::vector<bool> visible(tree_count);

	for (int row = 0; row < row_count; row++)
	{
		char max = 0;
		for (int col = 0; col < col_count; col++)
		{
			if (const char height = heights[row][col]; height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}

		max = 0;
		for (int col = col_count - 1; col >= 0; col--)
		{
			if (const char height = heights[row][col]; height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}
	}

	for (int col = 0; col < col_count; col++)
	{
		char max = 0;
		for (int row = 0; row < row_count; row++)
		{
			if (const char height = heights[row][col]; height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}

		max = 0;
		for (int row = row_count - 1; row >= 0; row--)
		{
			if (const char height = heights[row][col]; height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}
	}

	std::cout << std::accumulate(visible.begin(), visible.end(), 0);

	return 0;
}