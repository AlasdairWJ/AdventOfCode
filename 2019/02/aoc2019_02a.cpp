#include <iostream>
#include "intcode.hpp"

int main(int argc, const char* argv[])
{
	Program program;

	int value;
	while (std::cin >> value)
		program.push_back(value), std::cin.ignore(1);

	program[1] = 12;
	program[2] = 2;
	
	std::cout << execute(program);

	return 0;
}