#include <iostream>
#include <vector>
#include <algorithm> // std::ranges::max_element

int main(int _, const char*[])
{
	std::vector<int> inputs;

	for (int joltage; std::cin >> joltage; )
		inputs.push_back(joltage);

	const int max_joltage = *std::ranges::max_element(inputs);

	std::vector<bool> joltages(max_joltage + 1);

	for (const int joltage : inputs)
		joltages[joltage] = true;

	std::vector<long long> cumulative_joltages(max_joltage + 1);

	joltages[0] = true;
	cumulative_joltages[0] = 1;

	for (int j = 0; j < max_joltage; j++)
		if (joltages[j])
			for (int i = 1; i <= 3 && i + j <= max_joltage; i++)
				cumulative_joltages[j + i] += cumulative_joltages[j];

	std::cout << cumulative_joltages[max_joltage];
}