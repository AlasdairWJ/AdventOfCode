#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "../util/charconv.hpp"

int alphix(const char c) { return static_cast<int>(c - 'A'); }

enum Reigster
{
	A,
	B,
	C
};

enum Operation
{
	ADV = 0,
	BXL,
	BST,
	JNZ,
	BXC,
	OUT,
	BDV,
	CDV
};

int registers[3]{};

int combo(const int value)
{
	switch (value)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return value;
	case 4:
		return registers[A] & 0x7;
	case 5:
		return registers[B] & 0x7;
	case 6:
		return registers[C] & 0x7;
	default:
		return -1;
	}
}

int main(int argc, char const *argv[])
{

	const std::regex register_pattern{ "^Register ([ABC]): (\\d+)$" };
	const std::regex program_pattern{ "^Program: (.+)$" };

	for (std::string line; std::getline(std::cin, line) && !line.empty(); )
	{
		std::smatch match;
		std::regex_match(line, match, register_pattern);

		const int id = alphix(*match[1].first);
		const int value = util::from_chars(match[2]);

		registers[id] = value;
	}

	std::string line;
	std::getline(std::cin, line);

	std::smatch match;
	std::regex_match(line, match, program_pattern);

	const std::string_view program_str{ match[1].first, match[2].second };

	const auto program = program_str
		| std::views::split(',')
		| std::views::transform(util::from_chars_t{})
		| std::ranges::to<std::vector>();

	std::vector<int> output;

	for (int pos = 0; pos + 1 < program.size(); )
	{
		const int operation = program[pos];
		const int operand = program[pos + 1];

		bool cancel_inc = false;

		switch (operation)
		{
		case ADV:
			registers[A] >>= combo(operand);
			break;
		case BXL:
			registers[B] ^= operand;
			break;
		case BST:
			registers[B] = combo(operand);
			break;
		case JNZ:
			if (registers[A] != 0)
			{
				pos = operand;
				cancel_inc = true;
			}
			break;
		case BXC:
			registers[B] ^= registers[C];
			break;
		case OUT:
			output.push_back(combo(operand));
			break;
		case BDV:
			registers[B] = (registers[A] >> combo(operand));
			break;
		case CDV:
			registers[C] = (registers[A] >> combo(operand));
			break;
		default:
			break;
		}

		if (!cancel_inc)
			pos += 2;
	}

	std::cout << output.front();

	for (const int value : output | std::views::drop(1))
		std::cout << ',' << value;
}
