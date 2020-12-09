#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, const char* argv[])
{
	int affirmative[26] = {};

	int sum = 0;
	int people_count = 0;

	char line[64];
	while (gets_s(line, (unsigned)_countof(line)))
	{
		const int line_length = strlen(line);

		if (line_length == 0)
		{
			int count = 0;
			for (int i = 0; i < 26; i++)
			{
				if (affirmative[i] == people_count)
					count++;

				affirmative[i] = 0;
			}
			sum += count;
			people_count = 0;
			continue;
		}

		for (int i = 0; i < line_length; i++)
			affirmative[line[i] - 'a']++;
		
		people_count++;
	}

	int count = 0;
	for (int i = 0; i < 26; i++)
		if (affirmative[i] == people_count)
			count++;

	sum += count;

	printf("%d", sum);

	return 0;
}