#include <iostream>
#include <set>
#include <vector>
#include <ranges> // std::ranges::find, std::ranges::subrange, std::views::values
#include <algorithm> // std::ranges::minmax_element

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
	std::vector<std::pair<long long, long long>> cumulative_values;

	long long total = 0;

	long long value;
	for (int n = 1; std::cin >> value; n++)
	{
		if (n > preamble && !contains_values_that_sum(values, value))
			break;

		values.insert(value);
		cumulative_values.emplace_back(value, total);
		total += value;
	}

	for (auto it = cumulative_values.begin(); it != cumulative_values.end(); ++it)
	{
		const auto other_it = std::find_if(
			cumulative_values.begin(), it,
			[&it, &value](const auto& pair) {
				return it->second - pair.second == value;
			}
		);

		if (other_it != it)
		{
			auto values = std::ranges::subrange(other_it, it) | std::views::elements<0>;
			const auto [a, b] = std::ranges::minmax_element(values);
			std::cout << *a + *b;
			break;
		}
	}
}