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

	std::vector<__int64> cumulative_joltages(joltages.size());

	joltages[0] = true;
	cumulative_joltages[0] = 1;

	for (int j = 0; j < max_joltage; j++)
		if (joltages[j])
			for (int i = 1; i <= 3 && i + j <= max_joltage; i++)
				cumulative_joltages[j + i] += cumulative_joltages[j];

	std::cout << cumulative_joltages[max_joltage];
	
	return 0;
}