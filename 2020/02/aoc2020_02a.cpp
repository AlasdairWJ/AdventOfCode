#include <cstdio>
#include <cstdlib>

int main(int argc, const char* argv[])
{
	int valid_count = 0;

	char letter, password[64];
	int lower, upper;
	while (scanf_s("%d-%d %c: %s", &lower, &upper, &letter, 1, password, (unsigned)_countof(password)) == 4)
	{
		int letter_count = 0;

		for (int i = 0; password[i] != '\0'; i++)
			if (password[i] == letter)
				letter_count++;

		if (lower <= letter_count && letter_count <= upper)
			valid_count++;
	}

	printf("%d", valid_count);

	return 0;
}