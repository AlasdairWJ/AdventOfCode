#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <vector> // std::vector

int main(int argc, const char* argv[])
{
	std::vector<std::string> tree_sizes;

	std::string lines;
	while (std::getline(std::cin, lines))
		tree_sizes.push_back(lines);

	const int row_count = tree_sizes.size();
	const int col_count = tree_sizes.front().size();

	int max_scenic_score = 0;

	for (int row = 1; row < row_count - 1; row++)
	{
		for (int col = 1; col < col_count - 1; col++)
		{
			const char current_tree_size = tree_sizes[row][col];

			int r, c;
			char tree_size;

			int up_count = 0;
			for (r = row - 1, tree_size = '\0'; r >= 0 && tree_size < current_tree_size; r--, up_count++)
				tree_size = tree_sizes[r][col];

			int left_count = 0;
			for (c = col - 1, tree_size = '\0'; c >= 0 && tree_size < current_tree_size; c--, left_count++)
				tree_size = tree_sizes[row][c];

			int down_count = 0;
			for (r = row + 1, tree_size = '\0'; r < row_count && tree_size < current_tree_size; r++, down_count++)
				tree_size = tree_sizes[r][col];

			int right_count = 0;
			for (c = col + 1, tree_size = '\0'; c < col_count && tree_size < current_tree_size; c++, right_count++)
				tree_size = tree_sizes[row][c];

			if (const int score = up_count * left_count * down_count * right_count; score > max_scenic_score)
				max_scenic_score = score;
		}
	}

	std::cout << max_scenic_score;

	return 0;
}