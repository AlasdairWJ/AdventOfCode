#include <iostream>
#include <string> // std::getline
#include <regex> // std::regex, std::smatch, std::match_regex

#include "../../util/charconv.hpp" // util::from_chars

const std::regex instruction_re{ "^(addx|noop) ?(.+)?$" };

constexpr int key_cycles[]{
	20,
	60,
	100,
	140,
	180,
	220
};

int main(int _, const char*[])
{
	int signal_strength_sum = 0;

	int rgstr = 1;
	int key_id = 0;
	int cycle = 1;
	
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
}