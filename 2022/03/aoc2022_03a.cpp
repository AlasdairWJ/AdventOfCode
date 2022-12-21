#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <cctype>

int main(int argc, const char* argv[])
{
	int priority_sum = 0;

	std::string buffer;
	while (std::getline(std::cin, buffer))
	{
		const auto mid_point = buffer.begin() + buffer.size() / 2;
		std::set<char> a(buffer.begin(), mid_point),
					   b(mid_point, buffer.end());

		std::set<int> ix;
		std::set_intersection(a.begin(), a.end(),
							  b.begin(), b.end(),
							  std::inserter(ix, ix.begin()));

		const char letter = *ix.begin();
		priority_sum += islower(letter) ? (letter - 'a' + 1) : (letter - 'A' + 27);
		
	}

	std::cout << priority_sum;

	return 0;
}