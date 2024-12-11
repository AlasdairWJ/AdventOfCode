#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <ranges>
#include <numeric>

bool is_even(const int x) { return (x % 2) == 0; }

int digit_count(long long x)
{
	int d = 0;

	while (x > 0)
	{
		x /= 10;
		d++;
	}

	return d;
}

std::pair<long long, long long> split_digits(long long x, const int d)
{
	const long long p = std::pow(10ll, d); 
	return { x / p, x % p };
}

int main(int argc, char const *argv[])
{
	std::map<long long, long long> values;

	for (long long x; std::cin >> x; )
		values[x]++;

	for (int blink = 0; blink < 75; blink++)
	{
		decltype(values) next;

		for (const auto [stone, count] : values)
		{
			if (stone == 0)
			{
				next[1] += count;
			}
			else if (const int d = digit_count(stone); is_even(d))
			{
				const auto [left, right] = split_digits(stone, d / 2);

				next[left] += count;
				next[right] += count;
			}
			else
			{
				next[stone * 2024] += count;
			}
		}

		values.swap(next);
	}

	auto r = values | std::views::values;
	std::cout << std::accumulate(r.begin(), r.end(), 0ll);
}