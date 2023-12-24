#include <iostream>
#include <string> // std::getline
#include <vector>
#include <array>
#include <set>
#include <limits> // std::numeric_limits

constexpr int Inf = std::numeric_limits<int>::max();

constexpr int MinimumMoves = 4;
constexpr int MaximumMoves = 10;

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

	{
		int hl = 0;
		for (int n = 1; n < MinimumMoves; n++)
			hl += board[0][n];

		for (int n = MinimumMoves; n <= MaximumMoves; n++)
		{
			hl += board[0][n];
			heatLoss[0][n][0] = hl;
			states.emplace(n, 0, false);
		}
	}

	{
		int hl = 0;
		for (int n = 1; n < MinimumMoves; n++)
			hl += board[n][0];

		for (int n = MinimumMoves; n <= MaximumMoves; n++)
		{
			hl += board[n][0];
			heatLoss[n][0][1] = hl;
			states.emplace(0, n, true);
		}
	}

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
				if (x - MinimumMoves >= 0)
				{
					int hl = initialHL;

					for (int n = 1; n < MinimumMoves; n++)
						hl += board[y][x - n];

					for (int n = MinimumMoves; n <= MaximumMoves && x - n >= 0; n++)
					{
						hl += board[y][x - n];
						if (hl <= heatLoss[y][x - n][!o])
						{
							heatLoss[y][x - n][!o] = hl;
							nextStates.emplace(x - n, y, !o);
						}
					}
				}

				if (x + MinimumMoves < size)
				{
					int hl = initialHL;

					for (int n = 1; n < MinimumMoves; n++)
						hl += board[y][x + n];

					for (int n = MinimumMoves; n <= MaximumMoves && x + n < size; n++)
					{
						hl += board[y][x + n];
						if (hl <= heatLoss[y][x + n][!o])
						{
							heatLoss[y][x + n][!o] = hl;
							nextStates.emplace(x + n, y, !o);
						}
					}
				}
			}
			else
			{
				if (y - MinimumMoves >= 0)
				{
					int hl = initialHL;

					for (int n = 1; n < MinimumMoves; n++)
						hl += board[y - n][x];

					for (int n = MinimumMoves; n <= MaximumMoves && y - n >= 0; n++)
					{
						hl += board[y - n][x];
						if (hl <= heatLoss[y - n][x][!o])
						{
							heatLoss[y - n][x][!o] = hl;
							nextStates.emplace(x, y - n, !o);
						}
					}
				}

				if (y + MinimumMoves < size)
				{
					int hl = initialHL;

					for (int n = 1; n < MinimumMoves; n++)
						hl += board[y + n][x];

					for (int n = MinimumMoves; n <= MaximumMoves && y + n < size; n++)
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
		}	

		states.swap(nextStates);	
	}

	const auto& [z1, z2] = heatLoss[size - 1][size - 1];
	std::cout << std::min(z1, z2);
}