#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<std::string> heights;

	std::string buffer;
	while (std::getline(std::cin, buffer))
		heights.push_back(buffer);

	const int row_count = heights.size();
	const int col_count = heights.front().size();

	int max_scenic_score = 0;

	for (int row = 1; row < row_count - 1; row++)
	{
		for (int col = 1; col < col_count - 1; col++)
		{
			const char target_height = heights[row][col];

			char smallest_visible_tree = '\0';
			int down_count = 0;
			for (int r = row + 1; r < row_count; r++)
			{
				const char height = heights[r][col];
				if (smallest_visible_tree == '\0' || height > smallest_visible_tree)
				{
					smallest_visible_tree = smallest_visible_tree;
					down_count++;
				}
				if (height >= target_height)
					break;
			}

			smallest_visible_tree = '\0';
			int up_count = 0;
			for (int r = row - 1; r >= 0; r--)
			{
				const char height = heights[r][col];
				if (smallest_visible_tree == '\0' || height > smallest_visible_tree)
				{
					smallest_visible_tree = smallest_visible_tree;
					up_count++;
				}
				if (height >= target_height)
					break;
			}

			smallest_visible_tree = '\0';
			int right_count = 0;
			for (int c = col + 1; c < col_count; c++)
			{
				const char height = heights[row][c];
				if (smallest_visible_tree == '\0' || height > smallest_visible_tree)
				{
					smallest_visible_tree = smallest_visible_tree;
					right_count++;
				}
				if (height >= target_height)
					break;
			}

			smallest_visible_tree = '\0';
			int left_count = 0;
			for (int c = col - 1; c >= 0; c--)
			{
				const char height = heights[row][c];
				if (smallest_visible_tree == '\0' || height > smallest_visible_tree)
				{
					smallest_visible_tree = smallest_visible_tree;
					left_count++;
				}
				if (height >= target_height)
					break;
			}

			const int score = down_count * up_count * left_count * right_count;
			if (score > max_scenic_score)
				max_scenic_score = score;
		}
	}

	std::cout << max_scenic_score;

	return 0;
}