#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // std::count
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
	{ -1, -1 },
};

int main(int argc, const char* argv[])
{
	std::vector<std::string> board;

	std::string row;
	while (std::getline(std::cin, row))
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
					for (int x2 = x + dx, y2 = y + dy;
						x2 >= 0 && x2 <= max_x && y2 >= 0 && y2 <= max_y;
						x2 += dx, y2 += dy)
					{
						const char seat = board[y2][x2];
						if (seat != '.')
						{
							if (seat == '#')
								n++;

							break;
						}
					}
				}

				const char seat = board[y][x];
				if (seat == 'L' && n == 0)
				{
					next[y][x] = '#';
					any_updates = true;
				}
				else if (seat == '#' && n >= 5)
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