#include <iostream>
#include <vector>
#include <string>

constexpr int size = 12;

int main(int argc, const char* argv[])
{
	int total = 0;
	std::vector<int> tally;

	std::string binary;
	while (std::cin >> binary)
	{
		if (tally.empty())
			tally.resize(binary.size());
		
		for (int i = 0; i < size; i++)
			if (binary[i] == '1')
				tally[i]++;

		total++;
	}

	int gamma = 0, epsilon = 0;
	for (int i = tally.size() - 1, p = 1; i >= 0; i--, p <<= 1)
		((2 * tally[i] > total) ? gamma : epsilon) += p;

	std::cout << gamma * epsilon;

	return 0;
}