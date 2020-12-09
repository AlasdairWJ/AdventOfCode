#include <cstdio>

int main(int argc, const char* argv[])
{
	int lower, upper;
	if (scanf_s("%d-%d", &lower, &upper) != 2)
		return 1;

	int count = 0;

	int digits[6];
	for (int x = lower; x < upper; x++)
	{
		for (int d = 0, y = x; d < 6; d++, y /= 10)
			digits[d] = y % 10;

		bool is_increasing = true;
		for (int d = 0; d < 5; d++)
			if (digits[d] < digits[d + 1])
			{
				is_increasing = false;
				break;
			}

		if (!is_increasing)
			continue;

		int adjacent_digits = 0;
		for (int d = 0; d < 5; d++)
			if (digits[d] == digits[d + 1])
				adjacent_digits++;

		if (adjacent_digits == 0)
			continue;

		count++;
	}

	printf("%d", count);

	return 0;
}