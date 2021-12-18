#include <iostream>
#include <string>
#include <algorithm> // std::count, std::fill

int main(int argc, const char* argv[])
{
	int responses[26] = {};

	int sum = 0;
	int people_count = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			sum += std::count(std::begin(responses), std::end(responses), people_count);
			std::fill(std::begin(responses), std::end(responses), 0);
			people_count = 0;
			continue;
		}

		for (const char letter : line)
			responses[letter - 'a']++;
		
		people_count++;
	}

	sum += std::count(std::begin(responses), std::end(responses), people_count);

	std::cout << sum;

	return 0;
}