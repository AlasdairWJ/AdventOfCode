#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>

constexpr int BatteryCount = 12;

typedef long long i64;

int to_digit(const char c)
{
	return static_cast<int>(c - '0');
}

template <typename It>
void find_maximal(const It begin, const It end, const It out, const int count)
{
	if (count == 0)
		return;

	const auto last = end - count + 1;
	const auto it = std::max_element(begin, last);
	
	*out = *it;

	find_maximal(it + 1, end, out + 1, count - 1);
}

constexpr i64 concat_digit(const i64 a, const int b)
{
	return 10ll * a + b; 
}

int main()
{
	i64 total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::vector<int> digits(line.size());
		std::ranges::transform(line, digits.begin(), to_digit);

		std::vector<int> result(BatteryCount);
		find_maximal(digits.begin(), digits.end(), result.begin(), BatteryCount);

		total += std::accumulate(result.begin(), result.end(), i64{}, concat_digit);
	}

	std::cout << total;
}

