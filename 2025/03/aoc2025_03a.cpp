#include <iostream>
#include <string>

int digit(const char c)
{
	return static_cast<int>(c - '0'); 
}

int main()
{
	int total = 0;

	for (std::string line; std::getline(std::cin, line); )
	{
		const auto it_a = std::max_element(line.begin(), line.end() - 1);
		const auto it_b = std::max_element(it_a + 1, line.end());
		total += 10 * digit(*it_a) + digit(*it_b);
	}

	std::cout << total;
}

