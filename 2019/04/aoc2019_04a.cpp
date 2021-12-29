#include <iostream>

constexpr int num_digits = 6;

int main(int argc, const char* argv[])
{
	int lower;
	std::cin >> lower;

	std::cin.ignore(1); // '-'
	
	int upper;
	std::cin >> upper;

	int count = 0;

	int digits[num_digits];
	for (int x = lower; x < upper; x++)
	{
		for (int d = 0, y = x; d < num_digits; d++, y /= 10)
			digits[d] = y % 10;

		bool is_increasing = true;
		for (int d = 0; d < num_digits - 1; d++)
		{
			if (digits[d] < digits[d + 1])
			{
				is_increasing = false;
				break;
			}
		}

		if (!is_increasing)
			continue;

		bool any_adjacent_digits = false;
		for (int d = 0; d < num_digits - 1; d++)
		{
			if (digits[d] == digits[d + 1])
			{
				any_adjacent_digits = true;
				break;
			}
		}

		if (any_adjacent_digits)
			count++;
	}

	std::cout << count;

	return 0;
}