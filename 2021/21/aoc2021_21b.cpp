#include <iostream>
#include <string> // std::getline
#include <regex>
#include <map>
#include <cstdint>

#include "../../util/charconv.hpp" // util::from_chars

const std::regex starting_position_re{ "Player (\\d+) starting position: (\\d+)" };

constexpr int score_limit = 21;
constexpr int board_size = 10;

constexpr int dice_sides = 3;
constexpr int dice_rolls = 3;
constexpr int minimum_roll = dice_rolls;
constexpr int maximum_roll = dice_rolls * dice_sides;

struct State
{
	int positions[2];
	int scores[2];

	auto operator<=>(const State&) const = default;
};

int main(int argc, const char* argv[])
{
	State initialState{};

	for (int i = 0; i < 2; i++)
	{
		std::string line;
		std::getline(std::cin, line);

		std::smatch match;
		std::regex_match(line, match, starting_position_re);

		int player;
		util::from_chars(match[1], player);

		int position;
		util::from_chars(match[2], position);

		initialState.positions[player - 1] = position - 1;
	}

	int roll_dist[maximum_roll + 1]{};

	// lazy mans binomial distribution
	for (int a = 1; a <= dice_sides; a++)
		for (int b = 1; b <= dice_sides; b++)
			for (int c = 1; c <= dice_sides; c++)
				roll_dist[a + b + c]++;

	uint64_t wins[2]{};

	std::map<State, uint64_t> states;
	states[initialState] = 1;

	for (int p = 0; !states.empty(); p ^= 1)
	{
		std::map<State, uint64_t> next_states;

		for (const auto& [state, count] : states)
		{
			for (int roll = minimum_roll; roll <= maximum_roll; roll++)
			{
				State next_state = state;
				next_state.positions[p] += roll;
				next_state.positions[p] %= board_size;
				next_state.scores[p] += next_state.positions[p] + 1;

				if (next_state.scores[p] >= score_limit)
				{
					wins[p] += count * roll_dist[roll];
				}
				else
				{
					next_states[next_state] += count * roll_dist[roll];
				}
			}
		}

		states.swap(next_states);
	}

	std::cout << std::max(wins[0], wins[1]);
}