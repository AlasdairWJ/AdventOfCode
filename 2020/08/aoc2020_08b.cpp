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

bool is_valid_program(const Program& program, int& acc)
{
	int pc = 0;
	acc = 0;

	std::vector<bool> has_been_executed(program.size(), false);

	while (pc < program.size())
	{
		const auto& [op, value] = program[pc];

		if (has_been_executed[pc])
			return false;

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

	return true;
}

int main(int argc, const char* argv[])
{
	Program program;

	std::string op;
	int value;
	while (std::cin >> op, std::cin >> value)
		program.emplace_back(op_codes.find(op)->second, value);

	for (auto& [op, _] : program)
	{
		if (op == JMP)
		{
			op = NOP;

			int acc;
			if (is_valid_program(program, acc))
			{
				std::cout << acc;
				break;
			}

			op = JMP;
		}
		else if (op == NOP)
		{
			op = JMP;

			int acc;
			if (is_valid_program(program, acc))
			{
				std::cout << acc;
				break;
			}

			op = NOP;
		}
	}

	return 0;
}