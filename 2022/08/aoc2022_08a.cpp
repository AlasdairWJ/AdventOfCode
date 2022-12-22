#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <numeric>

int main(int argc, const char* argv[])
{
	std::vector<std::string> heights;

	std::string buffer;
	while (std::getline(std::cin, buffer))
		heights.push_back(buffer);

	const int row_count = heights.size();
	const int col_count = heights.front().size();
	const int tree_count = row_count * col_count;

	const auto visible = std::make_unique<bool[]>(tree_count);

	for (int row = 0; row < row_count; row++)
	{
		char max = 0;
		for (int col = 0; col < col_count; col++)
		{
			const char height = heights[row][col];
			if (height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}

		max = 0;
		for (int col = col_count - 1; col >= 0; col--)
		{
			const char height = heights[row][col];
			if (height > max)
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
			const char height = heights[row][col];
			if (height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}

		max = 0;
		for (int row = row_count - 1; row >= 0; row--)
		{
			const char height = heights[row][col];
			if (height > max)
			{
				max = height;
				visible[row * col_count + col] = true;
			}
		}
	}

	std::cout << std::accumulate(visible.get(), visible.get() + tree_count, 0);

	return 0;
}