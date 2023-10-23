#include <iostream>
#include <set>

constexpr int preamble = 25;

bool contains_values_that_sum(const std::set<long long>& values, const long long sum)
{
	return values.end() != std::ranges::find_if(values, [&](const long long a) {
		return values.end() != values.find(sum - a);
	});
}

int main(int _, const char*[])
{
	std::set<long long> values;

	long long value;
	for (int n = 1; std::cin >> value; n++)
	{
		if (n > preamble && !contains_values_that_sum(values, value))
			break;

		values.insert(value);
	}

	std::cout << value;
}