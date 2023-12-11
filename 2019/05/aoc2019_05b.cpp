#include <iostream>
#include "../Intcode/IntCPU.hpp"

int main(int argc, const char* argv[])
{
	const Program program = loadProgramFrom(std::cin);

	IntCPU cpu(program);
	cpu.input({ 5 });
	if (cpu.run() && !cpu.output().empty())
		std::cout << cpu.output().back();
}