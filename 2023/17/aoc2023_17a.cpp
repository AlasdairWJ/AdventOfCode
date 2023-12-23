#include <iostream>
#include <string> // std::getline
#include <vector>
#include <array>
#include <set>
#include <limits> // std::numeric_limits

constexpr int Inf = std::numeric_limits<int>::max();

struct State
{
	int x, y;
	int heatLoss;
	bool horizontal;

	auto operator<=>(const State&) const = default;
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

	std::set<State> states;

	heatLoss[0][0] = std::array{ 0, 0 };

	heatLoss[0][1][0] = board[0][1];
	states.emplace(1, 0, heatLoss[0][1][0], false);

	heatLoss[0][2][0] = board[0][1] + board[0][2];
	states.emplace(2, 0, heatLoss[0][2][0], false);

	heatLoss[1][0][1] = board[1][0];
	states.emplace(0, 1, heatLoss[1][0][1], true);

	heatLoss[2][0][1] = board[1][0] + board[2][0];
	states.emplace(0, 2, heatLoss[2][0][1], true);

	while (!states.empty())
	{
		decltype(states) nextStates;

		for (const auto& state : states)
		{
			if (state.x == size - 1 && state.y == size - 1)
				continue;

			if (state.horizontal)
			{
				for (int n = 1, hl = state.heatLoss; n <= 3 && state.x - n >= 0; n++)
				{
					hl += board[state.y][state.x - n];
					if (hl <= heatLoss[state.y][state.x - n][1])
					{
						heatLoss[state.y][state.x - n][1] = hl;
						nextStates.emplace(state.x - n, state.y, hl, false);
					}
				}

				for (int n = 1, hl = state.heatLoss; n <= 3 && state.x + n < size; n++)
				{
					hl += board[state.y][state.x + n];
					if (hl <= heatLoss[state.y][state.x + n][1])
					{
						heatLoss[state.y][state.x + n][1] = hl;
						nextStates.emplace(state.x + n, state.y, hl, false);
					}
				}
			}
			else
			{
				for (int n = 1, hl = state.heatLoss; n <= 3 && state.y - n >= 0; n++)
				{
					hl += board[state.y - n][state.x];
					if (hl <= heatLoss[state.y - n][state.x][0])
					{
						heatLoss[state.y - n][state.x][0] = hl;
						nextStates.emplace(state.x, state.y - n, hl, true);
					}
				}

				for (int n = 1, hl = state.heatLoss; n <= 3 && state.y + n < size; n++)
				{
					hl += board[state.y + n][state.x];
					if (hl <= heatLoss[state.y + n][state.x][0])
					{
						heatLoss[state.y + n][state.x][0] = hl;
						nextStates.emplace(state.x, state.y + n, hl, true);
					}
				}
			}
		}	

		states.swap(nextStates);	
	}

	const auto& [z1, z2] = heatLoss[size - 1][size - 1];
	std::cout << std::min(z1, z2);
}