#include <iostream>
#include <vector>

#include "Board.hpp"

int main(int argc, const char* argv[])
{
	std::vector<int> called;

	int value;
	char delim;
	do
	{
		std::cin >> value;
		std::cin >> delim;
		called.push_back(value);
	}
	while (delim == ',');

	std::vector<Board> boards;

	Board board;
	while (board.read())
		boards.push_back(board);

	for (const int call : called)
	{
		for (auto it = boards.begin(); it != boards.end();)
		{
			if (it->mark(call) && it->bingo())
			{
				if (boards.size() == 1)
				{
					printf("%d", it->sum() * call);
					return 0;
				}
				
				it = boards.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	return 0;
}