#include <iostream>
#include <cstdlib> // abs
#include <vector>
#include <algorithm> // std::minmax_element
#include <numeric> // std::accumulate

int tri(const int x) { return x * (x + 1) / 2; }

int main(int argc, const char* agv[])
{
	std::vector<int> positions;

	int value;
	while (std::cin >> value, std::cin.ignore(1))
		positions.push_back(value);

	const int pos = std::accumulate(positions.begin(), positions.end(), 0) / positions.size();

	int total = 0;
	for (const int p : positions)
		total += tri(abs(p - pos));

	std::cout << total;

	return 0;
}