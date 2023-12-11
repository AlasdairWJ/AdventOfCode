#include <iostream>
#include <algorithm> // std::ranges::all_of, std::ranges::contains
#include <ranges> // std::views::pairwise

constexpr int num_digits = 6;

const auto is_decreasing = [](const auto pair) { return pair.first >= pair.second; };

int main(int _, const char*[])
{
	int lower;
	std::cin >> lower;

	std::cin.ignore(1); // '-'
	
	int upper;
	std::cin >> upper;

	int count = 0;

	for (int x = lower; x < upper; x++)
	{
		int digits[num_digits], dist[10]{};
		for (int d = 0, y = x; d < num_digits; d++, y /= 10)
		{
			const int digit = y % 10;
			digits[d] = digit;
			dist[digit]++;
		}

		const bool all_decreasing = std::ranges::all_of(digits | std::views::pairwise, is_decreasing);

		if (all_decreasing && std::ranges::contains(dist, 2))
			count++;
	}

	std::cout << count;
}