#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int rgstr = 1;
	int cycle = 0;
	char display[6][41] = {};

	for (auto& row : display)
		std::fill(row, row + 40, ' ');

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		int operand = 0;
		int op_cycles = 1;

		if (buffer[0] == 'a')
		{
			operand = std::stoi(buffer.substr(5));
			op_cycles = 2;
		}

		for (int i = 0; i < op_cycles; i++, cycle++)
		{
			const int c = cycle % 40;
			if (rgstr - 1 <= c && c <= rgstr + 1)
			{
				const int r = cycle / 40;
				display[r][c] = '#';
			}
		}

		rgstr += operand;
	}

	for (const auto& row : display)
		std::cout << row << '\n';

	return 0;
}