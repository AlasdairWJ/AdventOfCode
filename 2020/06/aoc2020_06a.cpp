#include <iostream>
#include <string>
#include <algorithm> // std::count, std::fill 

int main(int _, const char*[])
{
	int sum = 0;

	while (std::cin)
	{
		bool responses[26]{};
		
		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		{
			for (const char letter : line)
				responses[letter - 'a'] = true;
		}

		sum += std::ranges::count(responses, true);
		std::ranges::fill(responses, false);
	}

	std::cout << sum;
}