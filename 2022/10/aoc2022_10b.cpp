#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <regex> // std::regex, std::smatch, std::match_regex

int main(int argc, const char* argv[])
{
	int rgstr = 1;
	int cycle = 0;
	char display[6][41] = {};

	for (auto& row : display)
		std::fill(row, row + 40, ' ');

	std::string line;
	while (std::getline(std::cin, line))
	{
		static const std::regex instruction_pattern{ "^(addx|noop)(?: (\\-?\\d+))?$" };

		std::smatch instruction_match;
		if (std::regex_match(line, instruction_match, instruction_pattern))
		{
			int operand = 0;
			int op_cycles = 1;

			if (line[0] == 'a')
			{
				operand = std::stoi(line.substr(5));
				op_cycles = 2;
			}

			for (int i = 0; i < op_cycles; i++, cycle++)
			{
				const int c = cycle % 40;
				if (rgstr - 1 <= c && c <= rgstr + 1)
				{
					const int r = cycle / 40;
					display[r][c] = '#';
				}
			}

			rgstr += operand;
		}
	}

	for (const auto& row : display)
		std::cout << row << '\n';

	return 0;
}