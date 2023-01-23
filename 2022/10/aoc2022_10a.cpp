#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <regex> // std::regex, std::smatch, std::match_regex

int main(int argc, const char* argv[])
{
	int rgstr = 1;

	int signal_strength_sum = 0;

	int key_id = 0;
	const int key_cycles[] {
		20,
		60,
		100,
		140,
		180,
		220
	};

	int cycle = 1;
	std::string line;
	while (std::getline(std::cin, line))
	{
		static const std::regex instruction_pattern{"^(addx|noop)(?: (\\-?\\d+))?$"};

		std::smatch instruction_match;
		if (std::regex_match(line, instruction_match, instruction_pattern))
		{
			int operand = 0;
			int op_cycles = 1;

			if (instruction_match.str(1) == "addx")
			{
				operand = std::stoi(instruction_match.str(2));
				op_cycles = 2;
			}

			for (int c = 0; c < op_cycles; c++, cycle++)
			{
				if (cycle == key_cycles[key_id])
				{
					signal_strength_sum += cycle * rgstr;
					key_id++;
				}
			}

			rgstr += operand;
		}
	}

	std::cout << signal_strength_sum;

	return 0;
}