#include <cstdio>

int main(int argc, const char* argv[])
{
	bool seated[1000] = {};

	char line[11];
	while (gets_s(line, (unsigned)_countof(line)))
	{
		int lower = 0, upper = 128;

		for (int i = 0; i < 7; i++)
		{
			if (line[i] == 'F')
				upper = (lower + upper) / 2;
			else if (line[i] == 'B')
				lower = (lower + upper) / 2;
		}

		const int row = lower;

		lower = 0, upper = 8;

		for (int i = 7; i < 11; i++)
		{
			if (line[i] == 'L')
				upper = (lower + upper) / 2;
			else if (line[i] == 'R')
				lower = (lower + upper) / 2;
		}

		const int column = lower;

		const int seat_id = 8 * row + column;

		seated[seat_id] = true;
	}

	for (int n = 1; n < 999; n++)
		if (!seated[n] && seated[n+1] && seated[n-1])
			printf("%d", n);

	return 0;
}