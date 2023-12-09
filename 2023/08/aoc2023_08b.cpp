#include <iostream>
#include <string>
#include <regex>
#include <map>

#include "../../util/numeric.hpp" // util::lcm

const std::regex map_pattern{ "(\\w+) \\= \\((\\w+), (\\w+)\\)" };

struct Destination
{
	std::string left;
	std::string right;
};

int main(int _, const char*[])
{
	std::string instructions;
	std::getline(std::cin, instructions);

	std::string line;
	std::getline(std::cin, line); // skip

	std::map<std::string, Destination> map;

	for (std::smatch match; std::getline(std::cin, line) && std::regex_match(line, match, map_pattern); )
	{
		auto& dest = map[match.str(1)];
		dest.left = match.str(2);
		dest.right = match.str(3);
	}

	// this would be hard in the general case!
	// assumptions we're making:
	// all loops are unique
	// all nodes will only visit one Z
	// we hit the Z at intervals with no offset

	int64_t result = 1;

	for (const auto& [node, _] : map)
	{
		if (node.back() == 'A')
		{
			int64_t steps = 0;
			int instr_ix = 0;

			std::string current = node;

			while (current.back() != 'Z')
			{
				current = instructions[instr_ix++] == 'L'
					? map[current].left
					: map[current].right;

				instr_ix %= instructions.size();

				steps++;
			}

			result = util::lcm(result, steps);
		}
	}

	std::cout << result;
}