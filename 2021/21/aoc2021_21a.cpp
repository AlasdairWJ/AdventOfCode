#include <iostream>
#include <string> // std::getline
#include <regex>

#include "../../util/charconv.hpp" // util::from_chars

const std::regex starting_position_re{ "Player (\\d+) starting position: (\\d+)" };

constexpr int score_limit = 1000;
constexpr int board_size = 10;

constexpr int dice_sides = 100;

int main(int argc, const char* argv[])
{
	int positions[2]{};

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

		positions[player - 1] = position - 1;
	}

	int currentRoll = 0;
	int rollCount = 0;
	auto dice = [&]() {
		rollCount++;
		const int result = currentRoll + 1;
		++currentRoll %= dice_sides;
		return result;
	};

	int scores[2]{};

	int p = 0;
	for (; scores[0] < score_limit && scores[1] < score_limit; p ^= 1)
	{
		const int roll = dice() + dice() + dice();
		positions[p] += roll;
		positions[p] %= board_size;

		scores[p] += positions[p] + 1;
	}

	std::cout << scores[p] * rollCount;
}