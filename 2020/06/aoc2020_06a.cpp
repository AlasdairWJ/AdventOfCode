#include <iostream>
#include <string>
#include <algorithm> // std::count, std::fill 

int main(int argc, const char* argv[])
{
	bool responses[26] = {};

	int sum = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			sum += std::count(std::begin(responses), std::end(responses), true);
			std::fill(std::begin(responses), std::end(responses), false);
			continue;
		}

		for (const char letter : line)
			responses[letter - 'a'] = true;
	}

	sum += std::count(std::begin(responses), std::end(responses), true);

	std::cout << sum;

	return 0;
}