#include <iostream>
#include "intcode.hpp"

constexpr int target = 19690720;

int main(int argc, const char* argv[])
{
	Program program;

	int value;
	while (std::cin >> value)
		program.push_back(value), std::cin.ignore(1);

	for (int noun = 0; noun < 100; noun++)
	{
		program[1] = noun;
		for (int verb = 0; verb < 100; verb++)
		{
			program[2] = verb;

			const int output = execute(program);
			if (output == target)
			{
				std::cout << 100 * noun + verb;
				return 0;
			}
		}
	}

	return 1;
}