#include <cstdio>
#include <vector>
#include <algorithm>

bool contains_values_that_sum(const std::vector<int>& values, int value)
{
	for (int i = 0; i < values.size(); i++)
		for (int j = i + 1; j < values.size(); j++)
			if (values[i] + values[j] == value)
				return true;
	return false;
}

bool find_contiguous_range_that_sums(const std::vector<__int64>& summed_values, int value, int& lower, int& upper)
{
	for (int i = 0; i < summed_values.size(); i++)
		for (int j = 0; j < i; j++)
			if (summed_values[i] - summed_values[j] == value)
			{
				lower = j;
				upper = i;
				return true;
			}
	return false;
}

int main(int argc, char const *argv[])
{
	std::vector<int> values;
	std::vector<__int64> summed_values;

	int n = 1;
	__int64 value, total = 0;
	while (scanf_s("%lld", &value) == 1)
	{
		if (n > 25 && !contains_values_that_sum(values, value))
			break;

		values.push_back(value);

		summed_values.push_back(total);
		total += value;
		n++;
	}

	int lower, upper;
	if (find_contiguous_range_that_sums(summed_values, value, lower, upper))
	{
		printf("%d", *std::max_element(values.begin() + lower, values.begin() + upper) +
					 *std::min_element(values.begin() + lower, values.begin() + upper));
	}

	return 1;
}