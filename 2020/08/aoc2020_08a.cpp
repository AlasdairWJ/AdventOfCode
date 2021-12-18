#include <iostream>
#include <string>
#include <vector>
#include <map>

enum OpCode { ACC, JMP, NOP };

const std::map<std::string, OpCode> op_codes
{
	{ "acc", ACC },
	{ "jmp", JMP },
	{ "nop", NOP }
};

using Program = std::vector<std::pair<OpCode, int>>;

int main(int argc, const char* argv[])
{
	Program program;

	std::string op;
	int value;
	while (std::cin >> op, std::cin >> value)
		program.emplace_back(op_codes.find(op)->second, value);

	std::vector<bool> has_been_executed(program.size());

	int acc = 0;
	int pc = 0;
	while (pc < program.size())
	{
		const auto& [op, value] = program[pc];

		if (has_been_executed[pc])
			break;

		has_been_executed[pc] = true;

		switch (op)
		{
		case ACC:
			acc += value;
			pc++;
			break;
		case JMP:
			pc += value;
			break;
		case NOP:
			pc++;
			break;
		default:
			break;
		}
	}

	std::cout << acc;

	return 0;
}