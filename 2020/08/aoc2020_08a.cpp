#include <iostream>
#include <string>
#include <vector>
#include <map>

enum class op_code_e { acc, jmp, nop };

int main(int _, const char*[])
{
	std::vector<std::pair<op_code_e, int>> program;

	for (std::string line; std::getline(std::cin, line); )
	{
		op_code_e op_code{};
		if (line.starts_with("acc"))
			op_code = op_code_e::acc;
		else if (line.starts_with("jmp"))
			op_code = op_code_e::jmp;
		else if (line.starts_with("nop"))
			op_code = op_code_e::nop;
		else
			continue;

		const int value = std::stoi(line.substr(4));

		program.emplace_back(op_code, value);
	}

	std::vector<bool> has_been_executed(program.size());

	int acc = 0;
	for (int pc = 0; pc < program.size(); )
	{
		const auto& [op, value] = program[pc];

		if (has_been_executed[pc])
			break;

		has_been_executed[pc] = true;

		switch (op)
		{
		case op_code_e::acc:
			acc += value;
			pc++;
			break;
		case op_code_e::jmp:
			pc += value;
			break;
		case op_code_e::nop:
			pc++;
			break;
		default:
			break;
		}
	}

	std::cout << acc;
}