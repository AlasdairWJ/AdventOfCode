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

	int settings[5] = { 5,6,7,8,9 };
	int max_signal = 0;

	do
	{
		intcode_machine_t intcode_machines[5];

		for (int i = 0; i < 5; i++)
		{
			auto &intcode_machine = intcode_machines[i];

			intcode_machine.load_program(intcode);

			std::queue<int> input({ settings[i] }), output;
			intcode_machine.execute(input, output);
		}

		bool has_halted = false;

		int signal = 0;
		while (!has_halted)
		{
			for (int i = 0; i < 5; i++)
			{
				std::queue<int> input({ signal }), output;
				execution_result_t result = intcode_machines[i].execute(input, output);

				if (i == 4 && result == HALTED)
					has_halted = true;

				signal = output.front();
			}
		}

		if (signal > max_signal)
			max_signal = signal;

	}
	while (std::next_permutation(settings, std::end(settings)));

	printf("%d", max_signal);

	return 0;
}