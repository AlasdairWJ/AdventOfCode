#include <iostream>
#include <string>
#include <regex>
#include <map>

const std::regex map_pattern{ "(\\w+) \\= \\((\\w+), (\\w+)\\)" };

constexpr std::string start{ "AAA" };
constexpr std::string finish{ "ZZZ" };

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

	int steps = 0;

	std::size_t instr_ix = 0;
	std::string current = start;

	do
	{
		current = instructions[instr_ix++] == 'L'
			? map[current].left
			: map[current].right;

		instr_ix %= instructions.size();

		steps++;
	}
	while (current != finish);

	std::cout << steps;
} 
