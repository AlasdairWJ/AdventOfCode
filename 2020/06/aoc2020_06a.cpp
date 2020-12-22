#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	bool affirmative[26] = {};

	int sum = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
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

		for (const char letter : line)
			affirmative[letter - 'a'] = true;
	}

	int count = 0;
	for (int i = 0; i < 26; i++)
		if (affirmative[i])
			count++;

	sum += count;

	std::cout << sum;

	return 0;
}