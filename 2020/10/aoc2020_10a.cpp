#include <cstdio>

#define N 200

int main(int argc, const char* argv[])
{
	bool joltages[N] = {};
	int max_joltage = 0;

	int joltage;
	while (scanf_s("%d", &joltage) == 1)
	{
		joltages[joltage] = true;
		if (joltage > max_joltage)
			max_joltage = joltage;
	}

	int total_differences[4] = {};

	for (int j = 0; j < max_joltage; )
		for (int i = 1; i <= 3; i++)
			if (joltages[j+i])
			{
				total_differences[i]++;
				j += i;
				break;
			}

	printf("%d", total_differences[1] * (total_differences[3] + 1));

	return 0;
}