#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>

int main(int argc, const char* argv[])
{
	int priority_sum = 0;

	std::string a, b, c;
	while (std::getline(std::cin, a) &&
		   std::getline(std::cin, b) &&
		   std::getline(std::cin, c))
	{
		std::set<char> a_letters(a.begin(), a.end()),
					   b_letters(b.begin(), b.end()),
					   c_letters(c.begin(), c.end());

		std::set<char> ix1, ix2;
		std::set_intersection(a_letters.begin(), a_letters.end(),
							  b_letters.begin(), b_letters.end(),
							  std::inserter(ix1, ix1.begin()));
		
		std::set_intersection(ix1.begin(), ix1.end(),
							  c_letters.begin(), c_letters.end(),
							  std::inserter(ix2, ix2.begin()));

		const char letter = *ix2.begin();
		priority_sum += islower(letter) ? (letter - 'a' + 1) : (letter - 'A' + 27);
	}

	std::cout << priority_sum;

	return 0;
}