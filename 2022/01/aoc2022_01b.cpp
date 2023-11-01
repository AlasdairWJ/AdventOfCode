#include <iostream>
#include <string> // std::getline
#include <numeric> // std::accumulate
#include <algorithm> // std::ranges::sort
#include <functional> // std::greater

#include "../../util/charconv.hpp" // util::from_chars

int main(int _, const char*[])
{
	std::vector<int> totals;
	
	while (std::cin)
	{
		int total = 0;

		for (std::string line; std::getline(std::cin, line) && !line.empty(); )
		{
			if (int value{}; util::from_chars(line, value))
				total += value;
		}

		totals.push_back(total);
	}

	std::ranges::sort(totals, std::greater());

	std::cout << std::accumulate(totals.begin(), totals.begin() + 3, 0);
}