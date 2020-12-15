#include <cstdio>

#define COLUMNS 25
#define ROWS 6

bool read_image(int (&digit_count)[10])
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			const char digit = getchar();
			if (digit == EOF)
				return false;
			digit_count[digit - '0']++;
		}
	}
	return true;
}

int main(int argc, const char* argv[])
{
	int min_zero_count = ROWS * COLUMNS;
	int min_product = 0;

	while (!feof(stdin))
	{
		int digit_count[10] = {};

		if (read_image(digit_count))
		{
			if (digit_count[0] < min_zero_count)
			{
				min_zero_count = digit_count[0];
				min_product = digit_count[1] * digit_count[2];
			}
		}	
	}

	printf("%d", min_product);

	return 0;
}