#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::ranges::count
#include <ranges> // std::views::join

const int deltas[][2]
{
	{ -1,  0 },
	{ -1,  1 },
	{  0,  1 },
	{  1,  1 },
	{  1,  0 },
	{  1, -1 },
	{  0, -1 },
	{ -1, -1 }
};

int main(int _, const char*[])
{
	std::vector<std::string> board;

	for (std::string row; std::getline(std::cin, row); )
		board.push_back(row);

	const int max_y = board.size() - 1;
	const int max_x = board[0].size() - 1;
 
	auto next = board;

	bool any_updates;

	do
	{
		any_updates = false;	
		for (int y = 0; y <= max_y; y++)
		{
			for (int x = 0; x <= max_x; x++)
			{
				int n = 0;
				for (const auto& [dx, dy] : deltas)
				{
					const int x2 = x + dx, y2 = y + dy;
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
	
	std::cout << std::ranges::count(board | std::views::join, '#');
}