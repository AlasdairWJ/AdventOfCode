#include <iostream>
#include "../Intcode/IntCPU.hpp"

int main(int _, const char*[])
{
	Program program = loadProgramFrom(std::cin);
	program[1] = 12;
	program[2] = 2;

	IntCPU cpu(program);

	cpu.run();

	std::cout << cpu.result();
}