#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::count

using Board = std::vector<std::string>;

const int deltas[][2]
{
	{ -1,  0 },
	{ -1,  1 },
	{  0,  1 },
	{  1,  1 },
	{  1,  0 },
	{  1, -1 },
	{  0, -1 },
	{ -1, -1 },
};

int main(int argc, const char* argv[])
{
	Board board;

	std::string row;
	while (std::getline(std::cin, row))
		board.push_back(row);

	const int max_y = board.size() - 1;
	const int max_x = board[0].size() - 1;
 
	Board next = board;

	bool any_updates;

	do
	{
		any_updates = false;	
		for (int y = 0; y <= max_y; y++)
		{
			for (int x = 0; x <= max_x; x++)
			{
				int n = 0;
				for (const auto& delta : deltas)
				{
					const int x2 = x + delta[0], y2 = y + delta[1];
					if (x2 >= 0 && x2 <= max_x && y2 >= 0 && y2 <= max_y)
						if (board[y2][x2] == '#')
							n++;
				}

				const char seat = board[y][x];
				if (seat == 'L' && n == 0)
				{
					next[y][x] = '#';
					any_updates = true;
				}
				else if (seat == '#' && n >= 4)
				{
					next[y][x] = 'L';
					any_updates = true;
				}
				else
				{
					next[y][x] = seat;
				}
			}
		}

		board.swap(next);
	}
	while (any_updates);
	
	int seated_count = 0;
	for (const auto& row : board)
		seated_count += std::count(row.begin(), row.end(), '#');

	std::cout << seated_count;

	return 0;
}