#include <iostream>
#include <string> // std::getline
#include <vector>

int main(int _, const char*[])
{
	std::vector<std::string> tree_sizes;

	for (std::string line; std::getline(std::cin, line); )
		tree_sizes.push_back(line);

	const int size = static_cast<int>(tree_sizes.size());

	int max_scenic_score = 0;

	for (int row = 1; row < size - 1; row++)
	{
		for (int col = 1; col < size - 1; col++)
		{
			const char current_tree_size = tree_sizes[row][col];

			int up_count = 0;
			for (int r = row - 1, tree_size = 0; r >= 0 && tree_size < current_tree_size; r--, up_count++)
				tree_size = tree_sizes[r][col];

			int left_count = 0;
			for (int c = col - 1, tree_size = 0; c >= 0 && tree_size < current_tree_size; c--, left_count++)
				tree_size = tree_sizes[row][c];

			int down_count = 0;
			for (int r = row + 1, tree_size = 0; r < size && tree_size < current_tree_size; r++, down_count++)
				tree_size = tree_sizes[r][col];

			int right_count = 0;
			for (int c = col + 1, tree_size = 0; c < size && tree_size < current_tree_size; c++, right_count++)
				tree_size = tree_sizes[row][c];

			if (const int score = up_count * left_count * down_count * right_count; score > max_scenic_score)
				max_scenic_score = score;
		}
	}

	std::cout << max_scenic_score;
}