#include <iostream>
#include <set>

constexpr int preamble = 25;

bool contains_values_that_sum(const std::set<int>& values, const int sum)
{
	for (const int a : values)
		if (const auto b = values.find(sum - a); b != values.end())
			return true;
	return false;
}

int main(int argc, const char* argv[])
{
	std::set<int> values;

	int n = 1;
	__int64 value;
	while (std::cin >> value)
	{
		if (n > preamble && !contains_values_that_sum(values, value))
			break;

		values.insert(value);
		n++;
	}

	std::cout << value;

	return 0;
}