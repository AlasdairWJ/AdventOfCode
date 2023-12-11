#include <iostream>
#include "../Intcode/IntCPU.hpp"

constexpr int target = 19690720;

int main(int argc, const char* argv[])
{
	Program program = loadProgramFrom(std::cin);

	for (int noun = 0; noun < 100; noun++)
	{
		program[1] = noun;
		for (int verb = 0; verb < 100; verb++)
		{
			program[2] = verb;

			IntCPU cpu(program);

			if (cpu.run() && cpu.result() == target)
			{
				std::cout << 100 * noun + verb;
				return 0;
			}
		}
	}
	
	return 1;
}