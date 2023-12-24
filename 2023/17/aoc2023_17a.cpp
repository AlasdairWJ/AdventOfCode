#include <iostream>
#include <string> // std::getline
#include <vector>
#include <array>
#include <set>
#include <limits> // std::numeric_limits

constexpr int Inf = std::numeric_limits<int>::max();

struct Position
{
	int x, y;
	bool horizontal;

	auto operator<=>(const Position&) const = default;
};

int main(int _, const char*[])
{
	std::vector<std::vector<int>> board;

	for (std::string line; std::getline(std::cin, line); )
	{
		auto& row = board.emplace_back(line.size());
		for (int i = 0; i < line.size(); i++)
			row[i] = int{ line[i] - '0' };
	}

	const int size = static_cast<int>(board.size());

	auto heatLoss = std::vector(
		size,
		std::vector(
			size, 
			std::array{ Inf, Inf }
		)
	);

	std::set<Position> states;

	heatLoss[0][0] = std::array{ 0, 0 };

	heatLoss[0][1][0] = board[0][1];
	states.emplace(1, 0, false);

	heatLoss[0][2][0] = board[0][1] + board[0][2];
	states.emplace(2, 0, false);

	heatLoss[1][0][1] = board[1][0];
	states.emplace(0, 1, true);

	heatLoss[2][0][1] = board[1][0] + board[2][0];
	states.emplace(0, 2, true);

	while (!states.empty())
	{
		decltype(states) nextStates;

		for (const auto& [x, y, o] : states)
		{
			if (x == size - 1 && y == size - 1)
				continue;

			const auto initialHL = heatLoss[y][x][o];

			if (o)
			{
				for (int n = 1, hl = initialHL; n <= 3 && x - n >= 0; n++)
				{
					hl += board[y][x - n];
					if (hl <= heatLoss[y][x - n][!o])
					{
						heatLoss[y][x - n][!o] = hl;
						nextStates.emplace(x - n, y, !o);
					}
				}

				for (int n = 1, hl = initialHL; n <= 3 && x + n < size; n++)
				{
					hl += board[y][x + n];
					if (hl <= heatLoss[y][x + n][!o])
					{
						heatLoss[y][x + n][!o] = hl;
						nextStates.emplace(x + n, y, !o);
					}
				}
			}
			else
			{
				for (int n = 1, hl = initialHL; n <= 3 && y - n >= 0; n++)
				{
					hl += board[y - n][x];
					if (hl <= heatLoss[y - n][x][!o])
					{
						heatLoss[y - n][x][!o] = hl;
						nextStates.emplace(x, y - n, !o);
					}
				}

				for (int n = 1, hl = initialHL; n <= 3 && y + n < size; n++)
				{
					hl += board[y + n][x];
					if (hl <= heatLoss[y + n][x][!o])
					{
						heatLoss[y + n][x][!o] = hl;
						nextStates.emplace(x, y + n, !o);
					}
				}
			}
		}	

		states.swap(nextStates);	
	}
	
	const auto& [z1, z2] = heatLoss[size - 1][size - 1];
	std::cout << std::min(z1, z2);
}