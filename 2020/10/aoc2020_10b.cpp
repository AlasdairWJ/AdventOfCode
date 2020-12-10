#include <cstdio>

#define N 200

int main(int argc, const char* argv[])
{
	bool joltages[N] = {};
	__int64 cumulative_joltages[N] = {};
	int max_joltage = 0;

	int joltage;
	while (scanf_s("%d", &joltage) == 1)
	{
		joltages[joltage] = true;
		if (joltage > max_joltage)
			max_joltage = joltage;
	}

	joltages[0] = true;
	cumulative_joltages[0] = 1;

	for (int j = 0; j < max_joltage; j++)
		if (joltages[j])
			for (int i = 1; i <= 3; i++)
				cumulative_joltages[j + i] += cumulative_joltages[j];

	printf("%lld", cumulative_joltages[max_joltage]);

	return 0;
}