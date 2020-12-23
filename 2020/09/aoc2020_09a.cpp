#include <cstdio>
#include <vector>

#define PREAMBLE_SIZE 25

bool contains_values_that_sum(const std::vector<int>& values, int sum)
{
	for (int i = 0; i < values.size(); i++)
		for (int j = i + 1; j < values.size(); j++)
			if (values[i] + values[j] == sum)
				return true;
	return false;
}

int main(int argc, char const *argv[])
{
	std::vector<int> values;

	int n = 1;
	__int64 value;
	while (scanf_s("%lld", &value) == 1)
	{
		if (n > PREAMBLE_SIZE && !contains_values_that_sum(values, value))
			break;

		values.push_back(value);
		n++;
	}

	printf("%lld", value);

	return 0;
}