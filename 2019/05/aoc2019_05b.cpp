#include <iostream>
#include <iterator>
#include "intcode.hpp"

int main(int argc, const char* argv[])
{
	Program program;

	int value;
	while (std::cin >> value)
		program.push_back(value), std::cin.ignore(1);

	std::vector<int> input { 5 }, output;
	execute(program, input.begin(), input.end(), std::back_inserter(output));

	std::cout << output.back();

	return 0;
}