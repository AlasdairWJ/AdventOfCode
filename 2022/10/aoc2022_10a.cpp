#include <iostream>
#include <string>
#include <queue>

int main(int argc, const char* argv[])
{
	int rgstr = 1;

	int signal_strength_sum = 0;

	const int key_cycles[] {
		20,
		60,
		100,
		140,
		180,
		220
	};

	const int *key_cycle = &key_cycles[0];

	int cycle = 1;
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

		for (int c = 0; c < op_cycles; c++, cycle++)
		{
			if (cycle == *key_cycle)
			{
				signal_strength_sum += cycle * rgstr;
				key_cycle++;
			}
		}

		rgstr += operand;
	}

	std::cout << signal_strength_sum;

	return 0;
}