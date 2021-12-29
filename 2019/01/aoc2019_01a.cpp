#include <iostream>

int main(int argc, const char* argv[])
{
	int total = 0;

	int value;
	while (std::cin >> value)
		total += (value / 3) - 2;

	std::cout << total;

	return 0;
}