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

	int total_differences[4]{};

	for (int j = 0; j < max_joltage; )
		for (int i = 1; i <= 3 && i + j <= max_joltage; i++)
			if (joltages[i + j])
			{
				total_differences[i]++;
				j += i;
				break;
			}

	std::cout << total_differences[1] * (total_differences[3] + 1);
}