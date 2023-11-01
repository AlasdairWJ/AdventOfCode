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
	std::ranges::set_intersection(r1, r2, std::inserter(ix, ix.end()));
	return ix;
}

int main(int _, const char*[])
{
	int priority_sum = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto middle_it = line.begin() + line.size() / 2;

		const auto letters = set_intersection<char>(
			std::set<char>{ line.begin(), middle_it },
			std::set<char>{ middle_it, line.end() }
		);

		const char letter = *letters.begin();

		priority_sum += std::islower(letter) ? int{ letter - 'a' + 1 } : int{ letter - 'A' + 27 };
	}

	std::cout << priority_sum;
}