#include <iostream>
#include <string>
#include <regex>
#include <vector>

#include "../util/charconv.hpp"

// I solved while doing repeated runs and updating these values
// I'll make it programmatic later

constexpr long long Offset = 18323965;
constexpr long long Increment = 1ll << 29;

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

long long registers[3]{};

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
		return static_cast<int>(registers[A] & 0x7);
	case 5:
		return static_cast<int>(registers[B] & 0x7);
	case 6:
		return static_cast<int>(registers[C] & 0x7);
	default:
		return -1;
	}
}

bool test(const auto& program)
{
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
		case OUT: {
			const int value = combo(operand);

			if (value != program[output.size()])
				return false;

			output.push_back(value);

			if (output.size() == program.size())
				return true;
		}
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

	return false;
}

int main(int argc, char const *argv[])
{
	std::string line;
	std::getline(std::cin, line);
	std::getline(std::cin, line);
	std::getline(std::cin, line);
	
	std::getline(std::cin, line);

	std::getline(std::cin, line);

	const std::regex program_pattern{ "^Program: (.+)$" };

	std::smatch match;
	std::regex_match(line, match, program_pattern);

	const std::string_view program_str{ match[1].first, match[2].second };

	const auto program = program_str
		| std::views::split(',')
		| std::views::transform(util::from_chars_t{})
		| std::ranges::to<std::vector>();

	long long x = Offset;
	for (;; x += Increment)
	{
		registers[A] = x;
		registers[B] = 0;
		registers[C] = 0;

		if (test(program))
		{
			std::cout << x;
			break;
		}
	}
}
