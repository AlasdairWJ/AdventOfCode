#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#include "intcode_machine.hpp"

int main(int argc, const char* argv[])
{
	std::vector<int> intcode;

	int value;
	while (scanf_s("%d,", &value) == 1)
		intcode.push_back(value);

	int settings[5] = {0,1,2,3,4};

	int max_signal = 0;

	do
	{
		int signal = 0;
		for (int i = 0; i < 5; i++)
		{
			intcode_machine_t intcode_machine(intcode);

			std::queue<int> input, output;

			input.push(settings[i]);
			input.push(signal);

			intcode_machine.execute(input, output);

			signal = output.front();
		}

		if (signal > max_signal)
			max_signal = signal;

	}
	while (std::next_permutation(settings, std::end(settings)));

	printf("%d", max_signal);

	return 0;
}