#include <iostream> // std::cout
#include <string> // std::string, std::getline
#include <set> // std::set
#include <algorithm> // std::set_intersection
#include <iterator> // std::inserter
#include <cctype> // std::islower

int main(int argc, const char* argv[])
{
	int priority_sum = 0;

	std::string line_a, line_b, line_c;
	while (std::getline(std::cin, line_a),
		   std::getline(std::cin, line_b),
		   std::getline(std::cin, line_c))
	{
		const std::set<char> a(line_a.begin(), line_a.end()),
							 b(line_b.begin(), line_b.end()),
							 c(line_c.begin(), line_c.end());

		std::set<char> d;
		std::set_intersection(a.begin(), a.end(),
							  b.begin(), b.end(),
							  std::inserter(d, d.begin()));

		std::set<char> e;
		std::set_intersection(c.begin(), c.end(),
							  d.begin(), d.end(),
							  std::inserter(e, e.begin()));

		const char letter = *e.begin();
		priority_sum += islower(letter) ? (letter - 'a' + 1) : (letter - 'A' + 27);
	}

	std::cout << priority_sum;

	return 0;
}