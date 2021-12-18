#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
	std::vector<bool> joltages;

	int joltage, max_joltage = -1;
	while (std::cin >> joltage)
	{
		if (joltage > max_joltage)
		{
			max_joltage = joltage;
			joltages.resize(max_joltage + 1);
		}
		joltages[joltage] = true;
	}

	int total_differences[4] = {};

	for (int j = 0; j < max_joltage; )
		for (int i = 1; i <= 3 && i + j <= max_joltage; i++)
			if (joltages[i + j])
			{
				total_differences[i]++;
				j += i;
				break;
			}

	std::cout << total_differences[1] * (total_differences[3] + 1);

	return 0;
}