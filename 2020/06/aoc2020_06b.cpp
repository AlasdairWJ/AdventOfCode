#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	int affirmative[26] = {};

	int sum = 0;
	int people_count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
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

		for (const char letter : line)
			affirmative[letter - 'a']++;
		
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