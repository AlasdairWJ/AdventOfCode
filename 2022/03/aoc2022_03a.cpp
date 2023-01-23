#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <set> // std::set
#include <algorithm> // std::set_intersection
#include <iterator> // std::inserter
#include <cctype> // std::islower

int main(int argc, const char* argv[])
{
	int priority_sum = 0;

	std::string line;
	while (std::getline(std::cin, line))
	{
		const auto mid_point = line.begin() + line.size() / 2;
		const std::set<char> a(line.begin(), mid_point),
							 b(mid_point, line.end());

		std::set<int> c;
		std::set_intersection(a.begin(), a.end(),
							  b.begin(), b.end(),
							  std::inserter(c, c.begin()));

		const char letter = *c.begin();
		priority_sum += std::islower(letter) ? (letter - 'a' + 1) : (letter - 'A' + 27);
	}

	std::cout << priority_sum;

	return 0;
}