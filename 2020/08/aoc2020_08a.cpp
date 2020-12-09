#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

enum Op { INVALID, ACC, JMP, NOP };

Op op_code_from_label(const char* label)
{
	if (strcmp(label, "acc") == 0) return ACC;
	if (strcmp(label, "jmp") == 0) return JMP;
	if (strcmp(label, "nop") == 0) return NOP;
	return INVALID;
}

int main(int argc, const char* argv[])
{
	std::vector<std::pair<Op, int>> program;

	{
		char operation[10];
		int value;
		while (scanf_s("%s %d", operation, (unsigned)_countof(operation), &value) == 2)
			program.emplace_back(op_code_from_label(operation), value);
	}

	std::vector<bool> has_been_executed(program.size());

	int acc = 0;
	int pc = 0;
	while (pc < program.size())
	{
		const auto& instruction = program[pc];

		if (has_been_executed[pc])
			break;

		has_been_executed[pc] = true;

		switch (instruction.first)
		{
		case ACC:
			acc += instruction.second;
			pc++;
			break;
		case JMP:
			pc += instruction.second;
			break;
		case NOP:
			pc++;
			break;
		default:
			break;
		}
	}

	printf("%d", acc);

	return 0;
}