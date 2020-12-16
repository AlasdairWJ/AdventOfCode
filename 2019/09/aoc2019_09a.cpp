#include <cstdio>

#include "intcode_machine.hpp"

int main(int argc, const char* argv[])
{
	std::vector<__int64> intcode;

	__int64 value;
	while (scanf_s("%lld,", &value) == 1)
		intcode.push_back(value);

	intcode_machine_t intcode_machine(intcode);

	std::queue<__int64> input, output;
	input.push(1);

	intcode_machine.execute(input, output);

	printf("%lld", output.front());

	return 0;
}