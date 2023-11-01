#include <iostream>
#include <string> // std::getline

#include "../../util/charconv.hpp" // util::from_chars

int main(int _, const char*[])
{
	int best = 0;

	while (std::cin)
	{
		int total = 0;

		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		{
			if (int value{}; util::from_chars(line, value))
				total += value;
		}

		if (best == 0 || total > best)
			best = total;
	}

	std::cout << best;
}