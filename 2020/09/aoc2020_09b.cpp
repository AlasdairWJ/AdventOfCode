#include <iostream>
#include <set>
#include <algorithm> // std::minmax_element

using ValuesSet = std::set<int>;

auto cmp_first_only = [](const auto& a, const auto& b) { return a.first < b.first; }; 
using CmpFirstOnly = decltype(cmp_first_only);

auto cmp_second_only = [](const auto& a, const auto& b) { return a.second < b.second; }; 
using CmpSecondOnly = decltype(cmp_second_only);

using SummedValuesSet = std::set<std::pair<__int64, int>, CmpFirstOnly>;
using SummedValuesSetIt = SummedValuesSet::const_iterator;

constexpr int preamble = 25;

bool contains_values_that_sum(const ValuesSet& values, const int sum)
{
	for (const int a : values)
		if (const auto b = values.find(sum - a); b != values.end())
			return true;
	return false;
}

bool find_contiguous_range_that_sums(const SummedValuesSet& summed_values, const __int64 target, SummedValuesSetIt& lower, SummedValuesSetIt& upper)
{
	for (auto a = summed_values.begin(); a != summed_values.end(); a++)
		if (const auto b = summed_values.find({ a->first - target, 0}); b != summed_values.end())
		{
			lower = b;
			upper = a;
			return true;
		}
	return false;
}


int main(int argc, const char* argv[])
{
	ValuesSet values;
	SummedValuesSet summed_values(cmp_first_only);

	int n = 1;
	int value;
	__int64 total = 0;
	while (std::cin >> value)
	{
		if (n > preamble && !contains_values_that_sum(values, value))
			break;

		values.insert(value);

		summed_values.emplace(total, value);
		total += value;
		n++;
	}

	std::cout << value << std::endl;

	SummedValuesSetIt lower, upper;
	if (find_contiguous_range_that_sums(summed_values, value, lower, upper))
	{
		const auto [a, b] = std::minmax_element(lower, upper, cmp_second_only);
		std::cout << a->second + b->second;
	}

	return 0;
}