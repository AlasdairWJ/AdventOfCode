#include <cstdio>
#include <cstdlib>

int main(int argc, const char* argv[])
{
	int valid_count = 0;

	char letter, password[64];
	int lower, upper;
	while (scanf_s("%d-%d %c: %s", &lower, &upper, &letter, 1, password, (unsigned)_countof(password)) == 4)
	{
		if ((password[lower-1] == letter) != (password[upper-1] == letter))
			valid_count++;
	}

	printf("%d", valid_count);

	return 0;
}