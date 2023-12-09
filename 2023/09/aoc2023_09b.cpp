#include <iostream>
#include <string>
#include <vector>
#include <ranges> // std::views::adjacent
#include <algorithm> // std::ranges::all_of

#include "../../util/charconv.hpp" // util::from_chars

int main(int _, const char*[])
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		std::vector<int> values;
		
		for (auto && r : line | std::views::split(' '))
		{
			if (int value; util::from_chars(r, value))
				values.push_back(value);
		}

		int next = values.front();
		int sign = -1;

		while (!std::ranges::all_of(values, [](int x) { return x == 0; }))
		{
			std::vector<int> differences;
			for (const auto [a, b] : values | std::views::adjacent<2>)
				differences.push_back(b - a);

			next += sign * differences.front();
			sign = -sign;

			values.swap(differences);
		}

		total += next;
	}

	std::cout << total;
}