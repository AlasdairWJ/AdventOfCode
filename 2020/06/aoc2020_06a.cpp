#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, const char* argv[])
{
	bool affirmative[26] = {};

	int sum = 0;

	char line[64];
	while (gets_s(line, (unsigned)_countof(line)))
	{
		const int line_length = strlen(line);

		if (line_length == 0)
		{
			int count = 0;
			for (int i = 0; i < 26; i++)
			{
				if (affirmative[i])
					count++;

				affirmative[i] = false;
			}
			sum += count;
			continue;
		}

		for (int i = 0; i < line_length; i++)
			affirmative[line[i] - 'a'] = true;
	}

	int count = 0;
	for (int i = 0; i < 26; i++)
		if (affirmative[i])
			count++;

	sum += count;

	printf("%d", sum);

	return 0;
}