#include <iostream>
#include <string> // std::getline
#include <set>
#include <algorithm> // std::set_intersection
#include <iterator> // std::inserter
#include <cctype> // std::islower

template <typename T>
auto set_intersection(auto && r1, auto && r2)
{
	std::set<T> ix;
	std::ranges::set_intersection(r1, r2, std::inserter(ix, ix.begin()));
	return ix;
}

int main(int _, const char*[])
{
	int priority_sum = 0;

	std::string lines[3];
	while (std::getline(std::cin, lines[0]) && std::getline(std::cin, lines[1]) && std::getline(std::cin, lines[2]))
	{
		std::ranges::sort(lines[0]);
		std::ranges::sort(lines[1]);
		std::ranges::sort(lines[2]);

		const auto letters = set_intersection<char>(
			set_intersection<char>(
				lines[0],
				lines[1]
			),
			lines[2]
		);

		const char letter = *letters.begin();

		priority_sum += std::islower(letter) ? int{ letter - 'a' + 1 } : int{ letter - 'A' + 27 };
	}

	std::cout << priority_sum;
}