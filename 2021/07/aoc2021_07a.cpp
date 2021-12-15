#include <iostream>
#include <cstdlib> // abs
#include <vector>
#include <algorithm> // std::sort

int main(int argc, const char* agv[])
{
	std::vector<int> positions;

	int value;
	while (std::cin >> value, std::cin.ignore(1))
		positions.push_back(value);

	std::sort(positions.begin(), positions.end());

	const int pos = positions[positions.size() / 2];
	
	int total = 0;
	for (const int p : positions)
		total += abs(p - pos);

	std::cout << total;

	return 0;
}