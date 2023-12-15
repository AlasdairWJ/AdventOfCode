#include <iostream>
#include <string> // std::getline
#include <ranges> // std::views::split

int main(int _, const char*[])
{
	int total = 0;

	std::string line;
	std::getline(std::cin, line);

	for (auto && r : line | std::views::split(','))
	{
		int hash = 0;

		for (const char c : r)
		{
			hash += c;
			hash *= 17;
			hash %= 256;
		}

		total += hash;
	}

	std::cout << total;
}