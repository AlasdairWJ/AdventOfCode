#include <iostream>
#include <string> // std::getline
#include <regex> // std::regex, std::smatch, std::match_regexc
#include <ranges> // std::views::join

#include "../../util/charconv.hpp" // util::from_chars

const std::regex instruction_re{ "^(addx|noop) ?(.+)?$" };

constexpr int N = 40;

int main(int _, const char*[])
{
	int rgstr = 1;
	int cycle = 0;
	char display[6][N]{};

	std::ranges::fill(display | std::views::join, ' ');

	for (std::string line; std::getline(std::cin, line); )
	{
		if (std::smatch match; std::regex_match(line, match, instruction_re))
		{
			int operand = 0;
			int op_cycles = 1;

			if (match.str(1) == "addx")
			{
				util::from_chars(match[2], operand);
				op_cycles = 2;
			}

			for (int i = 0; i < op_cycles; i++, cycle++)
			{
				const int c = cycle % N;
				if (rgstr - 1 <= c && c <= rgstr + 1)
				{
					const int r = cycle / N;
					display[r][c] = '#';
				}
			}

			rgstr += operand;
		}
	}

	for (const auto& row : display)
		std::cout.write(row, N) << '\n';
}